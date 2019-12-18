#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* hl; int rsize; char* render; int idx; int size; int hl_oc; } ;
typedef  TYPE_2__ erow ;
struct TYPE_8__ {int numrows; TYPE_2__* row; TYPE_1__* syntax; } ;
struct TYPE_6__ {char** keywords; char* singleline_comment_start; char* multiline_comment_start; char* multiline_comment_end; } ;

/* Variables and functions */
 TYPE_5__ E ; 
 int /*<<< orphan*/  HL_COMMENT ; 
 int /*<<< orphan*/  HL_KEYWORD1 ; 
 int /*<<< orphan*/  HL_KEYWORD2 ; 
 void* HL_MLCOMMENT ; 
 scalar_t__ HL_NONPRINT ; 
 int /*<<< orphan*/  HL_NORMAL ; 
 scalar_t__ HL_NUMBER ; 
 void* HL_STRING ; 
 int editorRowHasOpenComment (TYPE_2__*) ; 
 int is_separator (char) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  isprint (char) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* realloc (scalar_t__*,int) ; 
 int strlen (char*) ; 

void editorUpdateSyntax(erow *row) {
    row->hl = realloc(row->hl,row->rsize);
    memset(row->hl,HL_NORMAL,row->rsize);

    if (E.syntax == NULL) return; /* No syntax, everything is HL_NORMAL. */

    int i, prev_sep, in_string, in_comment;
    char *p;
    char **keywords = E.syntax->keywords;
    char *scs = E.syntax->singleline_comment_start;
    char *mcs = E.syntax->multiline_comment_start;
    char *mce = E.syntax->multiline_comment_end;

    /* Point to the first non-space char. */
    p = row->render;
    i = 0; /* Current char offset */
    while(*p && isspace(*p)) {
        p++;
        i++;
    }
    prev_sep = 1; /* Tell the parser if 'i' points to start of word. */
    in_string = 0; /* Are we inside "" or '' ? */
    in_comment = 0; /* Are we inside multi-line comment? */

    /* If the previous line has an open comment, this line starts
     * with an open comment state. */
    if (row->idx > 0 && editorRowHasOpenComment(&E.row[row->idx-1]))
        in_comment = 1;

    while(*p) {
        /* Handle // comments. */
        if (prev_sep && *p == scs[0] && *(p+1) == scs[1]) {
            /* From here to end is a comment */
            memset(row->hl+i,HL_COMMENT,row->size-i);
            return;
        }

        /* Handle multi line comments. */
        if (in_comment) {
            row->hl[i] = HL_MLCOMMENT;
            if (*p == mce[0] && *(p+1) == mce[1]) {
                row->hl[i+1] = HL_MLCOMMENT;
                p += 2; i += 2;
                in_comment = 0;
                prev_sep = 1;
                continue;
            } else {
                prev_sep = 0;
                p++; i++;
                continue;
            }
        } else if (*p == mcs[0] && *(p+1) == mcs[1]) {
            row->hl[i] = HL_MLCOMMENT;
            row->hl[i+1] = HL_MLCOMMENT;
            p += 2; i += 2;
            in_comment = 1;
            prev_sep = 0;
            continue;
        }

        /* Handle "" and '' */
        if (in_string) {
            row->hl[i] = HL_STRING;
            if (*p == '\\') {
                row->hl[i+1] = HL_STRING;
                p += 2; i += 2;
                prev_sep = 0;
                continue;
            }
            if (*p == in_string) in_string = 0;
            p++; i++;
            continue;
        } else {
            if (*p == '"' || *p == '\'') {
                in_string = *p;
                row->hl[i] = HL_STRING;
                p++; i++;
                prev_sep = 0;
                continue;
            }
        }

        /* Handle non printable chars. */
        if (!isprint(*p)) {
            row->hl[i] = HL_NONPRINT;
            p++; i++;
            prev_sep = 0;
            continue;
        }

        /* Handle numbers */
        if ((isdigit(*p) && (prev_sep || row->hl[i-1] == HL_NUMBER)) ||
            (*p == '.' && i >0 && row->hl[i-1] == HL_NUMBER)) {
            row->hl[i] = HL_NUMBER;
            p++; i++;
            prev_sep = 0;
            continue;
        }

        /* Handle keywords and lib calls */
        if (prev_sep) {
            int j;
            for (j = 0; keywords[j]; j++) {
                int klen = strlen(keywords[j]);
                int kw2 = keywords[j][klen-1] == '|';
                if (kw2) klen--;

                if (!memcmp(p,keywords[j],klen) &&
                    is_separator(*(p+klen)))
                {
                    /* Keyword */
                    memset(row->hl+i,kw2 ? HL_KEYWORD2 : HL_KEYWORD1,klen);
                    p += klen;
                    i += klen;
                    break;
                }
            }
            if (keywords[j] != NULL) {
                prev_sep = 0;
                continue; /* We had a keyword match */
            }
        }

        /* Not special chars */
        prev_sep = is_separator(*p);
        p++; i++;
    }

    /* Propagate syntax change to the next row if the open commen
     * state changed. This may recursively affect all the following rows
     * in the file. */
    int oc = editorRowHasOpenComment(row);
    if (row->hl_oc != oc && row->idx+1 < E.numrows)
        editorUpdateSyntax(&E.row[row->idx+1]);
    row->hl_oc = oc;
}
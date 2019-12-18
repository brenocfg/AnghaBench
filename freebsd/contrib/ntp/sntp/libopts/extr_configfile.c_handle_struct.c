#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tOptions ;
struct TYPE_3__ {scalar_t__ valType; } ;
typedef  TYPE_1__ tOptionValue ;
typedef  scalar_t__ tOptionLoadMode ;
typedef  int /*<<< orphan*/  tOptState ;

/* Variables and functions */
 char NUL ; 
 scalar_t__ OPARG_TYPE_STRING ; 
 scalar_t__ OPTION_LOAD_COOKED ; 
 char* SPN_VALUE_NAME_CHARS (char*) ; 
 int /*<<< orphan*/  SPN_WHITESPACE_CHARS (char*) ; 
 char* VOIDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cook_xml_text (char*) ; 
 int /*<<< orphan*/  load_opt_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 scalar_t__ option_load_mode ; 
 int /*<<< orphan*/  parse_attrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,TYPE_1__*) ; 
 char* strchr (char*,char) ; 
 char* trim_xml_text (char*,char*,scalar_t__) ; 

__attribute__((used)) static char *
handle_struct(tOptions * opts, tOptState * ost, char * txt, int dir)
{
    tOptionLoadMode mode = option_load_mode;
    tOptionValue    valu;

    char * pzName = ++txt;
    char * pzData;
    char * pcNulPoint;

    txt = SPN_VALUE_NAME_CHARS(txt);
    pcNulPoint = txt;
    valu.valType = OPARG_TYPE_STRING;

    switch (*txt) {
    case ' ':
    case '\t':
        txt = VOIDP(parse_attrs(
            opts, SPN_WHITESPACE_CHARS(txt), &mode, &valu));
        if (txt == NULL)
            return txt;
        if (*txt == '>')
            break;
        if (*txt != '/')
            return NULL;
        /* FALLTHROUGH */

    case '/':
        if (txt[1] != '>')
            return NULL;
        *txt = NUL;
        txt += 2;
        load_opt_line(opts, ost, pzName, dir, mode);
        return txt;

    case '>':
        break;

    default:
        txt = strchr(txt, '>');
        if (txt != NULL)
            txt++;
        return txt;
    }

    /*
     *  If we are here, we have a value.  "txt" points to a closing angle
     *  bracket.  Separate the name from the value for a moment.
     */
    *pcNulPoint = NUL;
    pzData = ++txt;
    txt = trim_xml_text(txt, pzName, mode);
    if (txt == NULL)
        return txt;

    /*
     *  Rejoin the name and value for parsing by "load_opt_line()".
     *  Erase any attributes parsed by "parse_attrs()".
     */
    memset(pcNulPoint, ' ', (size_t)(pzData - pcNulPoint));

    /*
     *  If we are getting a "string" value that is to be cooked,
     *  then process the XML-ish &xx; XML-ish and %XX hex characters.
     */
    if (  (valu.valType == OPARG_TYPE_STRING)
       && (mode == OPTION_LOAD_COOKED))
        cook_xml_text(pzData);

    /*
     *  "pzName" points to what looks like text for one option/configurable.
     *  It is NUL terminated.  Process it.
     */
    load_opt_line(opts, ost, pzName, dir, mode);

    return txt;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct blk_buf {int* s; int /*<<< orphan*/  len; } ;
struct Strbuf {int* s; int /*<<< orphan*/  len; } ;
typedef  int eChar ;
typedef  char Char ;

/* Variables and functions */
#define  DEOF 128 
 int DODOL ; 
 int DgetC (int) ; 
 scalar_t__ Dpack (struct blk_buf*) ; 
 int /*<<< orphan*/  ERR_UNMATCHED ; 
 int QUOTE ; 
 struct blk_buf* Strbuf_alloc () ; 
 int /*<<< orphan*/  Strbuf_append1 (struct blk_buf*,char) ; 
 char* Strbuf_finish (struct blk_buf*) ; 
 int /*<<< orphan*/  Strbuf_free ; 
 int TRIM ; 
 int /*<<< orphan*/  bb_append (struct blk_buf*,char*) ; 
 int /*<<< orphan*/  cleanup_ignore (struct blk_buf*) ; 
 int /*<<< orphan*/  cleanup_push (struct blk_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (struct blk_buf*) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unDgetC (int) ; 
 int /*<<< orphan*/  unDredc (int) ; 
 int /*<<< orphan*/  xfree (struct blk_buf*) ; 

__attribute__((used)) static int
Dword(struct blk_buf *bb)
{
    eChar c, c1;
    struct Strbuf *wbuf = Strbuf_alloc();
    int dolflg;
    int    sofar = 0;
    Char *str;

    cleanup_push(wbuf, Strbuf_free);
    for (;;) {
	c = DgetC(DODOL);
	switch (c) {

	case DEOF:
	    if (sofar == 0) {
		cleanup_until(wbuf);
		return (0);
	    }
	    /* finish this word and catch the code above the next time */
	    unDredc(c);
	    /*FALLTHROUGH*/

	case '\n':
	    goto end;

	case ' ':
	case '\t':
	    continue;

	case '`':
	    /* We preserve ` quotations which are done yet later */
	    Strbuf_append1(wbuf, (Char) c);
	    /*FALLTHROUGH*/
	case '\'':
	case '"':
	    /*
	     * Note that DgetC never returns a QUOTES character from an
	     * expansion, so only true input quotes will get us here or out.
	     */
	    c1 = c;
	    dolflg = c1 == '"' ? DODOL : 0;
	    for (;;) {
		c = DgetC(dolflg);
		if (c == c1)
		    break;
		if (c == '\n' || c == DEOF) {
		    cleanup_until(bb);
		    stderror(ERR_UNMATCHED, (int)c1);
		}
		if ((c & (QUOTE | TRIM)) == ('\n' | QUOTE)) {
		    if (wbuf->len != 0 && (wbuf->s[wbuf->len - 1] & TRIM) == '\\')
			wbuf->len--;
		}
		switch (c1) {

		case '"':
		    /*
		     * Leave any `s alone for later. Other chars are all
		     * quoted, thus `...` can tell it was within "...".
		     */
		    Strbuf_append1(wbuf, c == '`' ? '`' : c | QUOTE);
		    break;

		case '\'':
		    /* Prevent all further interpretation */
		    Strbuf_append1(wbuf, c | QUOTE);
		    break;

		case '`':
		    /* Leave all text alone for later */
		    Strbuf_append1(wbuf, (Char) c);
		    break;

		default:
		    break;
		}
	    }
	    if (c1 == '`')
		Strbuf_append1(wbuf, '`');
	    sofar = 1;
	    if (Dpack(wbuf) != 0)
		goto end;
	    continue;

	case '\\':
	    c = DgetC(0);	/* No $ subst! */
	    if (c == '\n' || c == DEOF)
		continue;
	    c |= QUOTE;
	    break;

	default:
	    break;
	}
	unDgetC(c);
	sofar = 1;
	if (Dpack(wbuf) != 0)
	    goto end;
    }

 end:
    cleanup_ignore(wbuf);
    cleanup_until(wbuf);
    str = Strbuf_finish(wbuf);
    bb_append(bb, str);
    xfree(wbuf);
    return 1;
}
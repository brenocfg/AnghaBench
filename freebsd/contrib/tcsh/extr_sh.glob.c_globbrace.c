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
struct blk_buf {int len; } ;
struct Strbuf {size_t len; int /*<<< orphan*/  s; } ;
typedef  scalar_t__ Char ;

/* Variables and functions */
 struct blk_buf BLK_BUF_INIT ; 
 scalar_t__ const EOS ; 
#define  LBRC 130 
#define  LBRK 129 
#define  RBRC 128 
 scalar_t__ const RBRK ; 
 struct Strbuf Strbuf_INIT ; 
 int /*<<< orphan*/  Strbuf_append (struct Strbuf*,scalar_t__ const*) ; 
 int /*<<< orphan*/  Strbuf_appendn (struct Strbuf*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  Strbuf_terminate (struct Strbuf*) ; 
 int /*<<< orphan*/  Strsave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bb_append (struct blk_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bb_cleanup (struct blk_buf*) ; 
 scalar_t__** bb_finish (struct blk_buf*) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
globbrace(const Char *s, Char ***bl)
{
    struct Strbuf gbuf = Strbuf_INIT;
    struct blk_buf bb = BLK_BUF_INIT;
    int     i;
    const Char *p, *pm, *pe, *pl;
    size_t prefix_len;

    /* copy part up to the brace */
    for (p = s; *p != LBRC; p++)
	;
    prefix_len = p - s;

    /* check for balanced braces */
    for (i = 0, pe = ++p; *pe; pe++)
	if (*pe == LBRK) {
	    /* Ignore everything between [] */
	    for (++pe; *pe != RBRK && *pe != EOS; pe++)
		continue;
	    if (*pe == EOS)
		return (-RBRK);
	}
	else if (*pe == LBRC)
	    i++;
	else if (*pe == RBRC) {
	    if (i == 0)
		break;
	    i--;
	}

    if (i != 0 || *pe == '\0')
	return (-RBRC);

    Strbuf_appendn(&gbuf, s, prefix_len);

    for (i = 0, pl = pm = p; pm <= pe; pm++)
	switch (*pm) {
	case LBRK:
	    for (++pm; *pm != RBRK && *pm != EOS; pm++)
		continue;
	    if (*pm == EOS) {
		bb_cleanup(&bb);
		xfree(gbuf.s);
		return (-RBRK);
	    }
	    break;
	case LBRC:
	    i++;
	    break;
	case RBRC:
	    if (i) {
		i--;
		break;
	    }
	    /* FALLTHROUGH */
	case ',':
	    if (i && *pm == ',')
		break;
	    else {
		gbuf.len = prefix_len;
		Strbuf_appendn(&gbuf, pl, pm - pl);
		Strbuf_append(&gbuf, pe + 1);
		Strbuf_terminate(&gbuf);
		bb_append(&bb, Strsave(gbuf.s));
		pl = pm + 1;
	    }
	    break;
	default:
	    break;
	}
    *bl = bb_finish(&bb);
    xfree(gbuf.s);
    return bb.len;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  xo_indent_by; int /*<<< orphan*/  xo_fmt; int /*<<< orphan*/  xo_data; int /*<<< orphan*/  xo_flush; int /*<<< orphan*/  xo_write; int /*<<< orphan*/  xo_opaque; } ;
typedef  TYPE_1__ xo_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  XOF_FLUSH_LINE ; 
 int /*<<< orphan*/  XOF_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOIF_CLEAR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOIF_INIT_IN_PROGRESS ; 
 scalar_t__ XOIF_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOIF_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XO_DEPTH ; 
 int /*<<< orphan*/  XO_INDENT_BY ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  xo_buf_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xo_depth_check (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_flush_file ; 
 scalar_t__ xo_is_line_buffered (int /*<<< orphan*/ ) ; 
 int xo_locale_inited ; 
 int /*<<< orphan*/  xo_write_to_file ; 

__attribute__((used)) static void
xo_init_handle (xo_handle_t *xop)
{
    xop->xo_opaque = stdout;
    xop->xo_write = xo_write_to_file;
    xop->xo_flush = xo_flush_file;

    if (xo_is_line_buffered(stdout))
	XOF_SET(xop, XOF_FLUSH_LINE);

    /*
     * We need to initialize the locale, which isn't really pretty.
     * Libraries should depend on their caller to set up the
     * environment.  But we really can't count on the caller to do
     * this, because well, they won't.  Trust me.
     */
    if (!xo_locale_inited) {
	xo_locale_inited = 1;	/* Only do this once */

#ifdef __FreeBSD__		/* Who does The Right Thing */
	const char *cp = "";
#else /* __FreeBSD__ */
	const char *cp = getenv("LC_ALL");
	if (cp == NULL)
	    cp = getenv("LC_CTYPE");
	if (cp == NULL)
	    cp = getenv("LANG");
	if (cp == NULL)
	    cp = "C";		/* Default for C programs */
#endif /* __FreeBSD__ */

	(void) setlocale(LC_CTYPE, cp);
    }

    /*
     * Initialize only the xo_buffers we know we'll need; the others
     * can be allocated as needed.
     */
    xo_buf_init(&xop->xo_data);
    xo_buf_init(&xop->xo_fmt);

    if (XOIF_ISSET(xop, XOIF_INIT_IN_PROGRESS))
	return;
    XOIF_SET(xop, XOIF_INIT_IN_PROGRESS);

    xop->xo_indent_by = XO_INDENT_BY;
    xo_depth_check(xop, XO_DEPTH);

    XOIF_CLEAR(xop, XOIF_INIT_IN_PROGRESS);
}
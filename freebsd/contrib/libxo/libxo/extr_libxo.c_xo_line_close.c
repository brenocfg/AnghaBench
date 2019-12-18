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
typedef  int /*<<< orphan*/  xo_handle_t ;
typedef  int /*<<< orphan*/  div_close ;

/* Variables and functions */
 int /*<<< orphan*/  XOF_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOF_PRETTY ; 
 int /*<<< orphan*/  XOIF_CLEAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOIF_DIV_OPEN ; 
 int /*<<< orphan*/  XOIF_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  XO_STYLE_HTML 129 
#define  XO_STYLE_TEXT 128 
 int /*<<< orphan*/  xo_data_append (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  xo_line_ensure_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xo_style (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xo_line_close (xo_handle_t *xop)
{
    static char div_close[] = "</div>";

    switch (xo_style(xop)) {
    case XO_STYLE_HTML:
	if (!XOIF_ISSET(xop, XOIF_DIV_OPEN))
	    xo_line_ensure_open(xop, 0);

	XOIF_CLEAR(xop, XOIF_DIV_OPEN);
	xo_data_append(xop, div_close, sizeof(div_close) - 1);

	if (XOF_ISSET(xop, XOF_PRETTY))
	    xo_data_append(xop, "\n", 1);
	break;

    case XO_STYLE_TEXT:
	xo_data_append(xop, "\n", 1);
	break;
    }
}
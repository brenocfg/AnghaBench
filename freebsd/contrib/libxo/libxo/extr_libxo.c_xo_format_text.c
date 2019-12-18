#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  xo_data; } ;
typedef  TYPE_1__ xo_handle_t ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  XO_STYLE_HTML 129 
#define  XO_STYLE_TEXT 128 
 int /*<<< orphan*/  xo_buf_append_div (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_buf_append_locale (TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int xo_style (TYPE_1__*) ; 

__attribute__((used)) static void
xo_format_text (xo_handle_t *xop, const char *str, ssize_t len)
{
    switch (xo_style(xop)) {
    case XO_STYLE_TEXT:
	xo_buf_append_locale(xop, &xop->xo_data, str, len);
	break;

    case XO_STYLE_HTML:
	xo_buf_append_div(xop, "text", 0, NULL, 0, str, len, NULL, 0, NULL, 0);
	break;
    }
}
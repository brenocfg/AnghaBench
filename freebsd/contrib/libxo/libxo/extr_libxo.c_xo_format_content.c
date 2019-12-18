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
typedef  int /*<<< orphan*/  xo_xff_flags_t ;
typedef  int /*<<< orphan*/  xo_handle_t ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  XO_STYLE_ENCODER 133 
#define  XO_STYLE_HTML 132 
#define  XO_STYLE_JSON 131 
#define  XO_STYLE_SDPARAMS 130 
#define  XO_STYLE_TEXT 129 
#define  XO_STYLE_XML 128 
 int /*<<< orphan*/  xo_buf_append_div (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_close_container_h (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  xo_format_value (int /*<<< orphan*/ *,char*,int,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_open_container_h (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  xo_simple_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xo_style (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xo_format_content (xo_handle_t *xop, const char *class_name,
		   const char *tag_name,
		   const char *value, ssize_t vlen,
		   const char *fmt, ssize_t flen,
		   xo_xff_flags_t flags)
{
    switch (xo_style(xop)) {
    case XO_STYLE_TEXT:
	xo_simple_field(xop, FALSE, value, vlen, fmt, flen, flags);
	break;

    case XO_STYLE_HTML:
	xo_buf_append_div(xop, class_name, flags, NULL, 0,
			  value, vlen, fmt, flen, NULL, 0);
	break;

    case XO_STYLE_XML:
    case XO_STYLE_JSON:
    case XO_STYLE_SDPARAMS:
	if (tag_name) {
	    xo_open_container_h(xop, tag_name);
	    xo_format_value(xop, "message", 7, value, vlen,
			    fmt, flen, NULL, 0, flags);
	    xo_close_container_h(xop, tag_name);

	} else {
	    /*
	     * Even though we don't care about labels, we need to do
	     * enough parsing work to skip over the right bits of xo_vap.
	     */
	    xo_simple_field(xop, TRUE, value, vlen, fmt, flen, flags);
	}
	break;

    case XO_STYLE_ENCODER:
	xo_simple_field(xop, TRUE, value, vlen, fmt, flen, flags);
	break;
    }
}
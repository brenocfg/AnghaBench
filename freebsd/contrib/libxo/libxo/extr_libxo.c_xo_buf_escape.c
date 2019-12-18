#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xo_xff_flags_t ;
typedef  int /*<<< orphan*/  xo_handle_t ;
struct TYPE_7__ {int /*<<< orphan*/  xb_curp; } ;
typedef  TYPE_1__ xo_buffer_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
#define  XO_STYLE_HTML 131 
#define  XO_STYLE_JSON 130 
#define  XO_STYLE_SDPARAMS 129 
#define  XO_STYLE_XML 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  xo_buf_has_room (TYPE_1__*,scalar_t__) ; 
 scalar_t__ xo_escape_json (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ xo_escape_sdparams (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ xo_escape_xml (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int xo_style (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xo_buf_escape (xo_handle_t *xop, xo_buffer_t *xbp,
	       const char *str, ssize_t len, xo_xff_flags_t flags)
{
    if (!xo_buf_has_room(xbp, len))
	return;

    memcpy(xbp->xb_curp, str, len);

    switch (xo_style(xop)) {
    case XO_STYLE_XML:
    case XO_STYLE_HTML:
	len = xo_escape_xml(xbp, len, flags);
	break;

    case XO_STYLE_JSON:
	len = xo_escape_json(xbp, len, flags);
	break;

    case XO_STYLE_SDPARAMS:
	len = xo_escape_sdparams(xbp, len, flags);
	break;
    }

    xbp->xb_curp += len;
}
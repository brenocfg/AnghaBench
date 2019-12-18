#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  xo_version; } ;
typedef  TYPE_1__ xo_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  XO_OP_VERSION ; 
#define  XO_STYLE_ENCODER 130 
#define  XO_STYLE_JSON 129 
#define  XO_STYLE_XML 128 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  xo_attr_h (TYPE_1__*,char*,char*,char const*) ; 
 TYPE_1__* xo_default (TYPE_1__*) ; 
 int /*<<< orphan*/  xo_encoder_handle (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_strndup (char const*,int) ; 
 int xo_style (TYPE_1__*) ; 
 int /*<<< orphan*/  xo_style_is_encoding (TYPE_1__*) ; 

void
xo_set_version_h (xo_handle_t *xop, const char *version)
{
    xop = xo_default(xop);

    if (version == NULL || strchr(version, '"') != NULL)
	return;

    if (!xo_style_is_encoding(xop))
	return;

    switch (xo_style(xop)) {
    case XO_STYLE_XML:
	/* For XML, we record this as an attribute for the first tag */
	xo_attr_h(xop, "version", "%s", version);
	break;

    case XO_STYLE_JSON:
	/*
	 * For JSON, we record the version string in our handle, and emit
	 * it in xo_emit_top.
	 */
	xop->xo_version = xo_strndup(version, -1);
	break;

    case XO_STYLE_ENCODER:
	xo_encoder_handle(xop, XO_OP_VERSION, NULL, version, 0);
	break;
    }
}
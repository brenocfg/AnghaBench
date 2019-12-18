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
struct TYPE_6__ {int /*<<< orphan*/ * xo_version; } ;
typedef  TYPE_1__ xo_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  XOIF_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOIF_TOP_EMITTED ; 
 int /*<<< orphan*/  xo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xo_indent (TYPE_1__*) ; 
 int /*<<< orphan*/  xo_printf (TYPE_1__*,char*,int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static void
xo_emit_top (xo_handle_t *xop, const char *ppn)
{
    xo_printf(xop, "%*s{%s", xo_indent(xop), "", ppn);
    XOIF_SET(xop, XOIF_TOP_EMITTED);

    if (xop->xo_version) {
	xo_printf(xop, "%*s\"__version\": \"%s\", %s",
		  xo_indent(xop), "", xop->xo_version, ppn);
	xo_free(xop->xo_version);
	xop->xo_version = NULL;
    }
}
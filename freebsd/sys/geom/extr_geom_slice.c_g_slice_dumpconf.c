#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uintmax_t ;
struct sbuf {int dummy; } ;
struct g_slicer {TYPE_1__* slices; } ;
struct g_provider {size_t index; } ;
struct g_geom {struct g_slicer* softc; } ;
struct g_consumer {int dummy; } ;
struct TYPE_2__ {scalar_t__ offset; scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 

void
g_slice_dumpconf(struct sbuf *sb, const char *indent, struct g_geom *gp, struct g_consumer *cp, struct g_provider *pp)
{
	struct g_slicer *gsp;

	gsp = gp->softc;
	if (indent == NULL) {
		sbuf_printf(sb, " i %u", pp->index);
		sbuf_printf(sb, " o %ju", 
		    (uintmax_t)gsp->slices[pp->index].offset);
		return;
	}
	if (pp != NULL) {
		sbuf_printf(sb, "%s<index>%u</index>\n", indent, pp->index);
		sbuf_printf(sb, "%s<length>%ju</length>\n",
		    indent, (uintmax_t)gsp->slices[pp->index].length);
		sbuf_printf(sb, "%s<seclength>%ju</seclength>\n", indent,
		    (uintmax_t)gsp->slices[pp->index].length / 512);
		sbuf_printf(sb, "%s<offset>%ju</offset>\n", indent,
		    (uintmax_t)gsp->slices[pp->index].offset);
		sbuf_printf(sb, "%s<secoffset>%ju</secoffset>\n", indent,
		    (uintmax_t)gsp->slices[pp->index].offset / 512);
	}
}
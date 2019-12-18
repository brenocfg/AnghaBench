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
struct sbuf {int dummy; } ;
struct cam_periph {int /*<<< orphan*/  unit_number; int /*<<< orphan*/  periph_name; } ;
struct TYPE_2__ {scalar_t__ announce_nosbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  xpt_announce_quirks (struct cam_periph*,int,char*) ; 
 TYPE_1__ xsoftc ; 

void
xpt_announce_quirks_sbuf(struct cam_periph *periph, struct sbuf *sb,
			 int quirks, char *bit_string)
{
	if (xsoftc.announce_nosbuf != 0) {
		xpt_announce_quirks(periph, quirks, bit_string);
		return;
	}

	if (quirks != 0) {
		sbuf_printf(sb, "%s%d: quirks=0x%b\n", periph->periph_name,
		    periph->unit_number, quirks, bit_string);
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct sbuf {int dummy; } ;
struct cam_path {TYPE_5__* device; TYPE_4__* target; TYPE_3__* bus; TYPE_1__* periph; } ;
struct TYPE_10__ {scalar_t__ lun_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  target_id; } ;
struct TYPE_8__ {TYPE_2__* sim; } ;
struct TYPE_7__ {int /*<<< orphan*/  bus_id; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  sim_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  unit_number; int /*<<< orphan*/  periph_name; } ;

/* Variables and functions */
 int sbuf_len (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 

int
xpt_path_sbuf(struct cam_path *path, struct sbuf *sb)
{

	if (path == NULL)
		sbuf_printf(sb, "(nopath): ");
	else {
		if (path->periph != NULL)
			sbuf_printf(sb, "(%s%d:", path->periph->periph_name,
				    path->periph->unit_number);
		else
			sbuf_printf(sb, "(noperiph:");

		if (path->bus != NULL)
			sbuf_printf(sb, "%s%d:%d:", path->bus->sim->sim_name,
				    path->bus->sim->unit_number,
				    path->bus->sim->bus_id);
		else
			sbuf_printf(sb, "nobus:");

		if (path->target != NULL)
			sbuf_printf(sb, "%d:", path->target->target_id);
		else
			sbuf_printf(sb, "X:");

		if (path->device != NULL)
			sbuf_printf(sb, "%jx): ",
			    (uintmax_t)path->device->lun_id);
		else
			sbuf_printf(sb, "X): ");
	}

	return(sbuf_len(sb));
}
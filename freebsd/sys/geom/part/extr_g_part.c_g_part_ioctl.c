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
typedef  int /*<<< orphan*/  u_long ;
struct thread {int dummy; } ;
struct g_provider {TYPE_1__* geom; } ;
struct g_part_table {int dummy; } ;
struct TYPE_2__ {struct g_part_table* softc; } ;

/* Variables and functions */
 int G_PART_IOCTL (struct g_part_table*,struct g_provider*,int /*<<< orphan*/ ,void*,int,struct thread*) ; 

__attribute__((used)) static int
g_part_ioctl(struct g_provider *pp, u_long cmd, void *data, int fflag, struct thread *td)
{
	struct g_part_table *table;

	table = pp->geom->softc;
	return G_PART_IOCTL(table, pp, cmd, data, fflag, td);
}
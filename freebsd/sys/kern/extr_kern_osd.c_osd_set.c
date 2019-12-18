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
typedef  int /*<<< orphan*/  u_int ;
struct osd {int dummy; } ;

/* Variables and functions */
 int osd_set_reserved (int /*<<< orphan*/ ,struct osd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 

int
osd_set(u_int type, struct osd *osd, u_int slot, void *value)
{

	return (osd_set_reserved(type, osd, slot, NULL, value));
}
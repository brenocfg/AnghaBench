#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int single_object; int /*<<< orphan*/ * list; int /*<<< orphan*/ * lbh; } ;
typedef  TYPE_1__ prop_data_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libbe_handle_t ;

/* Variables and functions */
 int be_proplist_update (TYPE_1__*) ; 

int
be_get_bootenv_props(libbe_handle_t *lbh, nvlist_t *dsnvl)
{
	prop_data_t data;

	data.lbh = lbh;
	data.list = dsnvl;
	data.single_object = false;
	return (be_proplist_update(&data));
}
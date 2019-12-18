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
struct TYPE_3__ {int /*<<< orphan*/  ctrl_online; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 

boolean_t pqisrc_ctrl_offline(pqisrc_softstate_t *softs)
{
	DBG_FUNC("IN\n");

	DBG_FUNC("OUT\n");

	return !softs->ctrl_online;
}
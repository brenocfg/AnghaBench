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

/* Variables and functions */
 int /*<<< orphan*/  IPFW_ADD_SOPT_HANDLER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scodes ; 
 int /*<<< orphan*/  vnet_mtx ; 

int
ipfw_iface_init()
{

	mtx_init(&vnet_mtx, "IPFW ifhandler mtx", NULL, MTX_DEF);
	IPFW_ADD_SOPT_HANDLER(1, scodes);
	return (0);
}
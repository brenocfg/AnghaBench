#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int vnet_initialized; } ;
typedef  TYPE_1__ kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  _kvm_vnet_selectpid (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 

int
_kvm_vnet_initialized(kvm_t *kd, int intialize)
{

	if (kd->vnet_initialized || !intialize)
		return (kd->vnet_initialized);

	(void) _kvm_vnet_selectpid(kd, getpid());

	return (kd->vnet_initialized);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* arch; } ;
typedef  TYPE_2__ kvm_t ;
struct TYPE_6__ {int (* ka_native ) (TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ ISALIVE (TYPE_2__*) ; 
 int stub1 (TYPE_2__*) ; 

int
kvm_native(kvm_t *kd)
{

	if (ISALIVE(kd))
		return (1);
	return (kd->arch->ka_native(kd));
}
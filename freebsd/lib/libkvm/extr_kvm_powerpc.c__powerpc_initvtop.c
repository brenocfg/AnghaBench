#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vmstate {int dummy; } ;
struct TYPE_5__ {struct vmstate* vmst; } ;
typedef  TYPE_1__ kvm_t ;

/* Variables and functions */
 scalar_t__ _kvm_malloc (TYPE_1__*,int) ; 
 int powerpc_maphdrs (TYPE_1__*) ; 

__attribute__((used)) static int
_powerpc_initvtop(kvm_t *kd)
{

	kd->vmst = (struct vmstate *)_kvm_malloc(kd, sizeof(*kd->vmst));
	if (kd->vmst == NULL)
		return (-1);

	if (powerpc_maphdrs(kd) == -1)
		return (-1);

	return (0);
}
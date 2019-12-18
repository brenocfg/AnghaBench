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
typedef  int /*<<< orphan*/  vmci_mutex ;

/* Variables and functions */
 int MTX_DEF ; 
 int MTX_NOWITNESS ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 

int
vmci_mutex_init(vmci_mutex *mutex, char *name)
{

	mtx_init(mutex, name, NULL, MTX_DEF | MTX_NOWITNESS);
	return (VMCI_SUCCESS);
}
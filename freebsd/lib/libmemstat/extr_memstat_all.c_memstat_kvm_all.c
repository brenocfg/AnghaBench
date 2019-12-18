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
struct memory_type_list {int dummy; } ;

/* Variables and functions */
 scalar_t__ memstat_kvm_malloc (struct memory_type_list*,void*) ; 
 scalar_t__ memstat_kvm_uma (struct memory_type_list*,void*) ; 

int
memstat_kvm_all(struct memory_type_list *mtlp, void *kvm_handle)
{

	if (memstat_kvm_malloc(mtlp, kvm_handle) < 0)
		return (-1);
	if (memstat_kvm_uma(mtlp, kvm_handle) < 0)
		return (-1);
	return (0);
}
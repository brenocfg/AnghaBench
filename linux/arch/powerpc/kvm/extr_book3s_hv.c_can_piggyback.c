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
struct kvmppc_vcore {int num_threads; } ;
struct core_info {int total_threads; } ;

/* Variables and functions */
 int can_dynamic_split (struct kvmppc_vcore*,struct core_info*) ; 

__attribute__((used)) static bool can_piggyback(struct kvmppc_vcore *pvc, struct core_info *cip,
			  int target_threads)
{
	if (cip->total_threads + pvc->num_threads > target_threads)
		return false;

	return can_dynamic_split(pvc, cip);
}
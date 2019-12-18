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
struct uv_hub_nmi_s {int /*<<< orphan*/  nmi_count; int /*<<< orphan*/  cpu_owner; int /*<<< orphan*/  in_nmi; } ;

/* Variables and functions */
 int atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uv_in_nmi ; 
 int /*<<< orphan*/  uv_nmi_cpu ; 

__attribute__((used)) static int uv_set_in_nmi(int cpu, struct uv_hub_nmi_s *hub_nmi)
{
	int first = atomic_add_unless(&hub_nmi->in_nmi, 1, 1);

	if (first) {
		atomic_set(&hub_nmi->cpu_owner, cpu);
		if (atomic_add_unless(&uv_in_nmi, 1, 1))
			atomic_set(&uv_nmi_cpu, cpu);

		atomic_inc(&hub_nmi->nmi_count);
	}
	return first;
}
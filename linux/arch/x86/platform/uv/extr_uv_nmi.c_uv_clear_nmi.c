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
struct uv_hub_nmi_s {int /*<<< orphan*/  nmi_lock; scalar_t__ hub_present; int /*<<< orphan*/  in_nmi; int /*<<< orphan*/  cpu_owner; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 struct uv_hub_nmi_s* uv_hub_nmi ; 
 int /*<<< orphan*/  uv_local_mmr_clear_nmi () ; 
 int /*<<< orphan*/  uv_reassert_nmi () ; 

__attribute__((used)) static inline void uv_clear_nmi(int cpu)
{
	struct uv_hub_nmi_s *hub_nmi = uv_hub_nmi;

	if (cpu == atomic_read(&hub_nmi->cpu_owner)) {
		atomic_set(&hub_nmi->cpu_owner, -1);
		atomic_set(&hub_nmi->in_nmi, 0);
		if (hub_nmi->hub_present)
			uv_local_mmr_clear_nmi();
		else
			uv_reassert_nmi();
		raw_spin_unlock(&hub_nmi->nmi_lock);
	}
}
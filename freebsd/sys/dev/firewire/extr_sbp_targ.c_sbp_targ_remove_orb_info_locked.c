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
struct sbp_targ_login {int /*<<< orphan*/  orbs; } ;
struct orb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct orb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  orb_info ; 

__attribute__((used)) static __inline void
sbp_targ_remove_orb_info_locked(struct sbp_targ_login *login, struct orb_info *orbi)
{
	STAILQ_REMOVE(&login->orbs, orbi, orb_info, link);
}
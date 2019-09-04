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
struct reflog_expire_cfg {int /*<<< orphan*/  expire_unreachable; int /*<<< orphan*/  expire_total; int /*<<< orphan*/  pattern; struct reflog_expire_cfg* next; } ;
struct cmd_reflog_expire_cb {int /*<<< orphan*/  expire_unreachable; int /*<<< orphan*/  expire_total; } ;

/* Variables and functions */
 int EXPIRE_TOTAL ; 
 int EXPIRE_UNREACH ; 
 int /*<<< orphan*/  default_reflog_expire ; 
 int /*<<< orphan*/  default_reflog_expire_unreachable ; 
 struct reflog_expire_cfg* reflog_expire_cfg ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  wildmatch (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_reflog_expiry_param(struct cmd_reflog_expire_cb *cb, int slot, const char *ref)
{
	struct reflog_expire_cfg *ent;

	if (slot == (EXPIRE_TOTAL|EXPIRE_UNREACH))
		return; /* both given explicitly -- nothing to tweak */

	for (ent = reflog_expire_cfg; ent; ent = ent->next) {
		if (!wildmatch(ent->pattern, ref, 0)) {
			if (!(slot & EXPIRE_TOTAL))
				cb->expire_total = ent->expire_total;
			if (!(slot & EXPIRE_UNREACH))
				cb->expire_unreachable = ent->expire_unreachable;
			return;
		}
	}

	/*
	 * If unconfigured, make stash never expire
	 */
	if (!strcmp(ref, "refs/stash")) {
		if (!(slot & EXPIRE_TOTAL))
			cb->expire_total = 0;
		if (!(slot & EXPIRE_UNREACH))
			cb->expire_unreachable = 0;
		return;
	}

	/* Nothing matched -- use the default value */
	if (!(slot & EXPIRE_TOTAL))
		cb->expire_total = default_reflog_expire;
	if (!(slot & EXPIRE_UNREACH))
		cb->expire_unreachable = default_reflog_expire_unreachable;
}
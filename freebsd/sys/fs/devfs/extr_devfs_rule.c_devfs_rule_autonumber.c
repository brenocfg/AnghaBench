#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct devfs_ruleset {int /*<<< orphan*/  ds_number; int /*<<< orphan*/  ds_rules; } ;
struct TYPE_2__ {int /*<<< orphan*/  dr_id; } ;
struct devfs_krule {TYPE_1__ dk_rule; } ;
typedef  scalar_t__ devfs_rnum ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct devfs_krule* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devfs_rule_byid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mkrid (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ rid2rn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rulehead ; 

__attribute__((used)) static int
devfs_rule_autonumber(struct devfs_ruleset *ds, devfs_rnum *rnump)
{
	struct devfs_krule *dk;

	/* Find the last rule. */
	dk = TAILQ_LAST(&ds->ds_rules, rulehead);
	if (dk == NULL)
		*rnump = 100;
	else {
		*rnump = rid2rn(dk->dk_rule.dr_id) + 100;
		/* Detect overflow. */
		if (*rnump < rid2rn(dk->dk_rule.dr_id))
			return (ERANGE);
	}
	KASSERT(devfs_rule_byid(mkrid(ds->ds_number, *rnump)) == NULL,
	    ("autonumbering resulted in an already existing rule"));
	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  alg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ WARN_ON (int) ; 
 TYPE_1__* alg_test_descs ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,...) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alg_check_test_descs_order(void)
{
	int i;

	for (i = 1; i < ARRAY_SIZE(alg_test_descs); i++) {
		int diff = strcmp(alg_test_descs[i - 1].alg,
				  alg_test_descs[i].alg);

		if (WARN_ON(diff > 0)) {
			pr_warn("testmgr: alg_test_descs entries in wrong order: '%s' before '%s'\n",
				alg_test_descs[i - 1].alg,
				alg_test_descs[i].alg);
		}

		if (WARN_ON(diff == 0)) {
			pr_warn("testmgr: duplicate alg_test_descs entry: '%s'\n",
				alg_test_descs[i].alg);
		}
	}
}
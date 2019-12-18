#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct shallow_info {unsigned int** used_shallow; int* need_reachability_test; int nr_ours; size_t* ours; int /*<<< orphan*/ * shallow_ref; TYPE_2__* shallow; TYPE_1__* ref; void* reachable; } ;
struct TYPE_4__ {int nr; } ;
struct TYPE_3__ {int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (unsigned int**,int) ; 
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  GIT_SHALLOW_FILE_ENVIRONMENT ; 
 int /*<<< orphan*/  alt_shallow_file ; 
 int /*<<< orphan*/  assign_shallow_commits_to_refs (struct shallow_info*,unsigned int**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setenv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* xcalloc (int,int) ; 

__attribute__((used)) static void prepare_shallow_update(struct shallow_info *si)
{
	int i, j, k, bitmap_size = DIV_ROUND_UP(si->ref->nr, 32);

	ALLOC_ARRAY(si->used_shallow, si->shallow->nr);
	assign_shallow_commits_to_refs(si, si->used_shallow, NULL);

	si->need_reachability_test =
		xcalloc(si->shallow->nr, sizeof(*si->need_reachability_test));
	si->reachable =
		xcalloc(si->shallow->nr, sizeof(*si->reachable));
	si->shallow_ref = xcalloc(si->ref->nr, sizeof(*si->shallow_ref));

	for (i = 0; i < si->nr_ours; i++)
		si->need_reachability_test[si->ours[i]] = 1;

	for (i = 0; i < si->shallow->nr; i++) {
		if (!si->used_shallow[i])
			continue;
		for (j = 0; j < bitmap_size; j++) {
			if (!si->used_shallow[i][j])
				continue;
			si->need_reachability_test[i]++;
			for (k = 0; k < 32; k++)
				if (si->used_shallow[i][j] & (1U << k))
					si->shallow_ref[j * 32 + k]++;
		}

		/*
		 * true for those associated with some refs and belong
		 * in "ours" list aka "step 7 not done yet"
		 */
		si->need_reachability_test[i] =
			si->need_reachability_test[i] > 1;
	}

	/*
	 * keep hooks happy by forcing a temporary shallow file via
	 * env variable because we can't add --shallow-file to every
	 * command. check_connected() will be done with
	 * true .git/shallow though.
	 */
	setenv(GIT_SHALLOW_FILE_ENVIRONMENT, alt_shallow_file, 1);
}
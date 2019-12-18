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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  ub ;
struct uma_bucket {int /*<<< orphan*/  ub_cnt; scalar_t__ ub_entries; } ;
struct bucketlist {int dummy; } ;
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 struct uma_bucket* LIST_FIRST (struct bucketlist*) ; 
 struct uma_bucket* LIST_NEXT (struct uma_bucket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int kread (int /*<<< orphan*/ *,struct uma_bucket*,struct uma_bucket*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_geterr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  ub_link ; 
 int /*<<< orphan*/  uma_print_bucket (struct uma_bucket*,char*) ; 

__attribute__((used)) static void
uma_print_bucketlist(kvm_t *kvm, struct bucketlist *bucketlist,
    const char *name, const char *spaces)
{
	struct uma_bucket *ubp, ub;
	uint64_t total_entries, total_cnt;
	int count, ret;

	printf("%s%s {", spaces, name);

	total_entries = total_cnt = 0;
	count = 0;
	for (ubp = LIST_FIRST(bucketlist); ubp != NULL; ubp =
	    LIST_NEXT(&ub, ub_link)) {
		ret = kread(kvm, ubp, &ub, sizeof(ub), 0);
		if (ret != 0)
			errx(-1, "uma_print_bucketlist: %s", kvm_geterr(kvm));
		if (count % 2 == 0)
			printf("\n%s  ", spaces);
		uma_print_bucket(&ub, "");
		printf(" ");
		total_entries += ub.ub_entries;
		total_cnt += ub.ub_cnt;
		count++;
	}

	printf("\n");
	printf("%s};  // total cnt %ju, total entries %ju\n", spaces,
	    total_cnt, total_entries);
}
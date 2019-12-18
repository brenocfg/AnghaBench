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
struct testgroup_t {int dummy; } ;
struct TYPE_2__ {scalar_t__* tests; scalar_t__ name; } ;

/* Variables and functions */
 TYPE_1__* cfg_aliases ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int process_test_option (struct testgroup_t*,scalar_t__) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static int
process_test_alias(struct testgroup_t *groups, const char *test)
{
	int i, j, n, r;
	for (i=0; cfg_aliases && cfg_aliases[i].name; ++i) {
		if (!strcmp(cfg_aliases[i].name, test)) {
			n = 0;
			for (j = 0; cfg_aliases[i].tests[j]; ++j) {
				r = process_test_option(groups, cfg_aliases[i].tests[j]);
				if (r<0)
					return -1;
				n += r;
			}
			return n;
		}
	}
	printf("No such test alias as @%s!",test);
	return -1;
}
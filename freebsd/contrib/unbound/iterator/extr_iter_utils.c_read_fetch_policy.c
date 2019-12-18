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
struct iter_env {int max_dependency_depth; int* target_fetch_policy; } ;

/* Variables and functions */
 scalar_t__ calloc (size_t,int) ; 
 int cfg_count_numbers (char const*) ; 
 int /*<<< orphan*/  fetch_fill (struct iter_env*,char const*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 

__attribute__((used)) static int
read_fetch_policy(struct iter_env* ie, const char* str)
{
	int count = cfg_count_numbers(str);
	if(count < 1) {
		log_err("Cannot parse target fetch policy: \"%s\"", str);
		return 0;
	}
	ie->max_dependency_depth = count - 1;
	ie->target_fetch_policy = (int*)calloc(
		(size_t)ie->max_dependency_depth+1, sizeof(int));
	if(!ie->target_fetch_policy) {
		log_err("alloc fetch policy: out of memory");
		return 0;
	}
	fetch_fill(ie, str);
	return 1;
}
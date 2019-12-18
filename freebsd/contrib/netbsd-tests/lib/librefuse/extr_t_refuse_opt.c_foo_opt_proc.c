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
struct fuse_args {int dummy; } ;
struct foofs_config {int /*<<< orphan*/ * nonopt; } ;

/* Variables and functions */
 int FUSE_OPT_KEY_NONOPT ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static int foo_opt_proc(void *data, const char *arg, int key, struct fuse_args *outargs) {
	struct foofs_config *config = data;

	if (key == FUSE_OPT_KEY_NONOPT && config->nonopt == NULL) {
		config->nonopt = strdup(arg);
		return 0;
	}
	else {
		return 1;
	}
}
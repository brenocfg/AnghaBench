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
struct TYPE_2__ {scalar_t__ nr; } ;
struct remote {TYPE_1__ push; } ;
struct branch {char const** merge_name; int /*<<< orphan*/  refname; scalar_t__ merge_nr; } ;

/* Variables and functions */
 char* apply_refspecs (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* pushremote_for_branch (struct branch*,int /*<<< orphan*/ *) ; 
 struct remote* remote_get (char const*) ; 

const char *remote_ref_for_branch(struct branch *branch, int for_push,
				  int *explicit)
{
	if (branch) {
		if (!for_push) {
			if (branch->merge_nr) {
				if (explicit)
					*explicit = 1;
				return branch->merge_name[0];
			}
		} else {
			const char *dst, *remote_name =
				pushremote_for_branch(branch, NULL);
			struct remote *remote = remote_get(remote_name);

			if (remote && remote->push.nr &&
			    (dst = apply_refspecs(&remote->push,
						  branch->refname))) {
				if (explicit)
					*explicit = 1;
				return dst;
			}
		}
	}
	if (explicit)
		*explicit = 0;
	return "";
}
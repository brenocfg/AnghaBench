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
struct remote {int dummy; } ;
struct branch {int dummy; } ;

/* Variables and functions */
#define  PUSH_DEFAULT_CURRENT 133 
#define  PUSH_DEFAULT_MATCHING 132 
#define  PUSH_DEFAULT_NOTHING 131 
#define  PUSH_DEFAULT_SIMPLE 130 
#define  PUSH_DEFAULT_UNSPECIFIED 129 
#define  PUSH_DEFAULT_UPSTREAM 128 
 int /*<<< orphan*/  _ (char*) ; 
 struct branch* branch_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int is_workflow_triangular (struct remote*) ; 
 int push_default ; 
 int /*<<< orphan*/  refspec_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rs ; 
 int /*<<< orphan*/  setup_push_current (struct remote*,struct branch*) ; 
 int /*<<< orphan*/  setup_push_upstream (struct remote*,struct branch*,int,int) ; 

__attribute__((used)) static void setup_default_push_refspecs(struct remote *remote)
{
	struct branch *branch = branch_get(NULL);
	int triangular = is_workflow_triangular(remote);

	switch (push_default) {
	default:
	case PUSH_DEFAULT_MATCHING:
		refspec_append(&rs, ":");
		break;

	case PUSH_DEFAULT_UNSPECIFIED:
	case PUSH_DEFAULT_SIMPLE:
		if (triangular)
			setup_push_current(remote, branch);
		else
			setup_push_upstream(remote, branch, triangular, 1);
		break;

	case PUSH_DEFAULT_UPSTREAM:
		setup_push_upstream(remote, branch, triangular, 0);
		break;

	case PUSH_DEFAULT_CURRENT:
		setup_push_current(remote, branch);
		break;

	case PUSH_DEFAULT_NOTHING:
		die(_("You didn't specify any refspecs to push, and "
		    "push.default is \"nothing\"."));
		break;
	}
}
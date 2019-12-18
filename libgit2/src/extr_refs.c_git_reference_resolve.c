#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  symbolic; } ;
struct TYPE_11__ {TYPE_2__ target; TYPE_1__* db; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ git_reference ;
struct TYPE_9__ {int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
#define  GIT_REFERENCE_DIRECT 129 
#define  GIT_REFERENCE_SYMBOLIC 128 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_reference_lookup (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_reference_lookup_resolved (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int git_reference_type (TYPE_3__ const*) ; 

int git_reference_resolve(git_reference **ref_out, const git_reference *ref)
{
	switch (git_reference_type(ref)) {
	case GIT_REFERENCE_DIRECT:
		return git_reference_lookup(ref_out, ref->db->repo, ref->name);

	case GIT_REFERENCE_SYMBOLIC:
		return git_reference_lookup_resolved(ref_out, ref->db->repo, ref->target.symbolic, -1);

	default:
		git_error_set(GIT_ERROR_REFERENCE, "invalid reference");
		return -1;
	}
}
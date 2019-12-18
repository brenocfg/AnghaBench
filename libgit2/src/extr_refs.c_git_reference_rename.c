#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_signature ;
struct TYPE_8__ {TYPE_1__* db; } ;
typedef  TYPE_2__ git_reference ;
struct TYPE_7__ {int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int git_reference__log_signature (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int reference__rename (TYPE_2__**,TYPE_2__*,char const*,int,int /*<<< orphan*/ *,char const*) ; 

int git_reference_rename(
	git_reference **out,
	git_reference *ref,
	const char *new_name,
	int force,
	const char *log_message)
{
	git_signature *who;
	int error;

	assert(out && ref);

	if ((error = git_reference__log_signature(&who, ref->db->repo)) < 0)
		return error;

	error = reference__rename(out, ref, new_name, force, who, log_message);
	git_signature_free(who);

	return error;
}
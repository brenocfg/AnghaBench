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
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/  const*) ; 
 int git_reference__log_signature (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int reference__create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int git_reference_create_matching(
	git_reference **ref_out,
	git_repository *repo,
	const char *name,
	const git_oid *id,
	int force,
	const git_oid *old_id,
	const char *log_message)

{
	int error;
	git_signature *who = NULL;

	assert(id);

	if ((error = git_reference__log_signature(&who, repo)) < 0)
		return error;

	error = reference__create(
		ref_out, repo, name, id, NULL, force, who, log_message, old_id, NULL);

	git_signature_free(who);
	return error;
}
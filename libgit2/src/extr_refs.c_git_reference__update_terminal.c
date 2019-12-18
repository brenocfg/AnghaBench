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
typedef  int /*<<< orphan*/  const git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_7__ {char const* symbolic; int /*<<< orphan*/  oid; } ;
struct TYPE_8__ {char const* name; TYPE_1__ target; } ;
typedef  TYPE_2__ git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 scalar_t__ GIT_REFERENCE_DIRECT ; 
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int get_terminal (TYPE_2__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_reference__log_signature (int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_2__*) ; 
 scalar_t__ git_reference_type (TYPE_2__*) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/  const*) ; 
 int reference__create (TYPE_2__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_reference__update_terminal(
	git_repository *repo,
	const char *ref_name,
	const git_oid *oid,
	const git_signature *sig,
	const char *log_message)
{
	git_reference *ref = NULL, *ref2 = NULL;
	git_signature *who = NULL;
	const git_signature *to_use;
	int error = 0;

	if (!sig && (error = git_reference__log_signature(&who, repo)) < 0)
		return error;

	to_use = sig ? sig : who;
	error = get_terminal(&ref, repo, ref_name, 0);

	/* found a dangling symref */
	if (error == GIT_ENOTFOUND && ref) {
		assert(git_reference_type(ref) == GIT_REFERENCE_SYMBOLIC);
		git_error_clear();
		error = reference__create(&ref2, repo, ref->target.symbolic, oid, NULL, 0, to_use,
					  log_message, NULL, NULL);
	} else if (error == GIT_ENOTFOUND) {
		git_error_clear();
		error = reference__create(&ref2, repo, ref_name, oid, NULL, 0, to_use,
					  log_message, NULL, NULL);
	}  else if (error == 0) {
		assert(git_reference_type(ref) == GIT_REFERENCE_DIRECT);
		error = reference__create(&ref2, repo, ref->name, oid, NULL, 1, to_use,
					  log_message, &ref->target.oid, NULL);
	}

	git_reference_free(ref2);
	git_reference_free(ref);
	git_signature_free(who);
	return error;
}
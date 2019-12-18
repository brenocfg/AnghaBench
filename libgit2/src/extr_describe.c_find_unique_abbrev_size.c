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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int GIT_EAMBIGUOUS ; 
 size_t GIT_OID_HEXSZ ; 
 int git_odb_exists_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int git_repository_odb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_unique_abbrev_size(
	int *out,
	git_repository *repo,
	const git_oid *oid_in,
	unsigned int abbreviated_size)
{
	size_t size = abbreviated_size;
	git_odb *odb;
	git_oid dummy;
	int error;

	if ((error = git_repository_odb__weakptr(&odb, repo)) < 0)
		return error;

	while (size < GIT_OID_HEXSZ) {
		if ((error = git_odb_exists_prefix(&dummy, odb, oid_in, size)) == 0) {
			*out = (int) size;
			return 0;
		}

		/* If the error wasn't that it's not unique, then it's a proper error */
		if (error != GIT_EAMBIGUOUS)
			return error;

		/* Try again with a larger size */
		size++;
	}

	/* If we didn't find any shorter prefix, we have to do the whole thing */
	*out = GIT_OID_HEXSZ;

	return 0;
}
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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_object ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_commit_create_with_signature (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,char*) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_read (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_odb (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_commit_write__attach_multiline_signature(void)
{
		const char *gpgsig = "-----BEGIN PGP SIGNATURE-----\n\
Version: GnuPG v1.4.12 (Darwin)\n\
\n\
iQIcBAABAgAGBQJQ+FMIAAoJEH+LfPdZDSs1e3EQAJMjhqjWF+WkGLHju7pTw2al\n\
o6IoMAhv0Z/LHlWhzBd9e7JeCnanRt12bAU7yvYp9+Z+z+dbwqLwDoFp8LVuigl8\n\
JGLcnwiUW3rSvhjdCp9irdb4+bhKUnKUzSdsR2CK4/hC0N2i/HOvMYX+BRsvqweq\n\
AsAkA6dAWh+gAfedrBUkCTGhlNYoetjdakWqlGL1TiKAefEZrtA1TpPkGn92vbLq\n\
SphFRUY9hVn1ZBWrT3hEpvAIcZag3rTOiRVT1X1flj8B2vGCEr3RrcwOIZikpdaW\n\
who/X3xh/DGbI2RbuxmmJpxxP/8dsVchRJJzBwG+yhwU/iN3MlV2c5D69tls/Dok\n\
6VbyU4lm/ae0y3yR83D9dUlkycOnmmlBAHKIZ9qUts9X7mWJf0+yy2QxJVpjaTGG\n\
cmnQKKPeNIhGJk2ENnnnzjEve7L7YJQF6itbx5VCOcsGh3Ocb3YR7DMdWjt7f8pu\n\
c6j+q1rP7EpE2afUN/geSlp5i3x8aXZPDj67jImbVCE/Q1X9voCtyzGJH7MXR0N9\n\
ZpRF8yzveRfMH8bwAJjSOGAFF5XkcR/RNY95o+J+QcgBLdX48h+ZdNmUf6jqlu3J\n\
7KmTXXQcOVpN6dD3CmRFsbjq+x6RHwa8u1iGn+oIkX908r97ckfB/kHKH7ZdXIJc\n\
cpxtDQQMGYFpXK/71stq\n\
=ozeK\n\
-----END PGP SIGNATURE-----";

	const char *data =  "tree 4b825dc642cb6eb9a060e54bf8d69288fbee4904\n\
parent 8496071c1b46c854b31185ea97743be6a8774479\n\
author Ben Burkert <ben@benburkert.com> 1358451456 -0800\n\
committer Ben Burkert <ben@benburkert.com> 1358451456 -0800\n\
\n\
a simple commit which works\n";

const char *complete = "tree 4b825dc642cb6eb9a060e54bf8d69288fbee4904\n\
parent 8496071c1b46c854b31185ea97743be6a8774479\n\
author Ben Burkert <ben@benburkert.com> 1358451456 -0800\n\
committer Ben Burkert <ben@benburkert.com> 1358451456 -0800\n\
gpgsig -----BEGIN PGP SIGNATURE-----\n\
 Version: GnuPG v1.4.12 (Darwin)\n\
 \n\
 iQIcBAABAgAGBQJQ+FMIAAoJEH+LfPdZDSs1e3EQAJMjhqjWF+WkGLHju7pTw2al\n\
 o6IoMAhv0Z/LHlWhzBd9e7JeCnanRt12bAU7yvYp9+Z+z+dbwqLwDoFp8LVuigl8\n\
 JGLcnwiUW3rSvhjdCp9irdb4+bhKUnKUzSdsR2CK4/hC0N2i/HOvMYX+BRsvqweq\n\
 AsAkA6dAWh+gAfedrBUkCTGhlNYoetjdakWqlGL1TiKAefEZrtA1TpPkGn92vbLq\n\
 SphFRUY9hVn1ZBWrT3hEpvAIcZag3rTOiRVT1X1flj8B2vGCEr3RrcwOIZikpdaW\n\
 who/X3xh/DGbI2RbuxmmJpxxP/8dsVchRJJzBwG+yhwU/iN3MlV2c5D69tls/Dok\n\
 6VbyU4lm/ae0y3yR83D9dUlkycOnmmlBAHKIZ9qUts9X7mWJf0+yy2QxJVpjaTGG\n\
 cmnQKKPeNIhGJk2ENnnnzjEve7L7YJQF6itbx5VCOcsGh3Ocb3YR7DMdWjt7f8pu\n\
 c6j+q1rP7EpE2afUN/geSlp5i3x8aXZPDj67jImbVCE/Q1X9voCtyzGJH7MXR0N9\n\
 ZpRF8yzveRfMH8bwAJjSOGAFF5XkcR/RNY95o+J+QcgBLdX48h+ZdNmUf6jqlu3J\n\
 7KmTXXQcOVpN6dD3CmRFsbjq+x6RHwa8u1iGn+oIkX908r97ckfB/kHKH7ZdXIJc\n\
 cpxtDQQMGYFpXK/71stq\n\
 =ozeK\n\
 -----END PGP SIGNATURE-----\n\
\n\
a simple commit which works\n";

	git_oid one, two;
	git_odb *odb;
	git_odb_object *obj;

	cl_git_pass(git_commit_create_with_signature(&one, g_repo, data, gpgsig, "gpgsig"));
	cl_git_pass(git_commit_create_with_signature(&two, g_repo, data, gpgsig, NULL));

	cl_assert(!git_oid_cmp(&one, &two));
	cl_git_pass(git_repository_odb(&odb, g_repo));
	cl_git_pass(git_odb_read(&obj, odb, &one));
	cl_assert_equal_s(complete, git_odb_object_data(obj));

	git_odb_object_free(obj);
	git_odb_free(odb);
}
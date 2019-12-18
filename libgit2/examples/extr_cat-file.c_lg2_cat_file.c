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
struct opts {char* member_0; int action; scalar_t__ verbose; int /*<<< orphan*/ * rev; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; } ;
typedef  int /*<<< orphan*/  oidstr ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_tag ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_odb_object ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
#define  GIT_OBJECT_BLOB 135 
#define  GIT_OBJECT_COMMIT 134 
#define  GIT_OBJECT_TAG 133 
#define  GIT_OBJECT_TREE 132 
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
#define  SHOW_NONE 131 
#define  SHOW_PRETTY 130 
#define  SHOW_SIZE 129 
#define  SHOW_TYPE 128 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_type (int /*<<< orphan*/ *) ; 
 char* git_object_type2string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_odb_object_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_read (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_tostr (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_odb (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_opts (struct opts*,int,char**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  show_blob (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  show_commit (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  show_tag (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  show_tree (int /*<<< orphan*/  const*) ; 

int lg2_cat_file(git_repository *repo, int argc, char *argv[])
{
	struct opts o = { ".", NULL, 0, 0 };
	git_object *obj = NULL;
	char oidstr[GIT_OID_HEXSZ + 1];

	parse_opts(&o, argc, argv);

	check_lg2(git_revparse_single(&obj, repo, o.rev),
			"Could not resolve", o.rev);

	if (o.verbose) {
		char oidstr[GIT_OID_HEXSZ + 1];
		git_oid_tostr(oidstr, sizeof(oidstr), git_object_id(obj));

		printf("%s %s\n--\n",
			git_object_type2string(git_object_type(obj)), oidstr);
	}

	switch (o.action) {
	case SHOW_TYPE:
		printf("%s\n", git_object_type2string(git_object_type(obj)));
		break;
	case SHOW_SIZE: {
		git_odb *odb;
		git_odb_object *odbobj;

		check_lg2(git_repository_odb(&odb, repo), "Could not open ODB", NULL);
		check_lg2(git_odb_read(&odbobj, odb, git_object_id(obj)),
			"Could not find obj", NULL);

		printf("%ld\n", (long)git_odb_object_size(odbobj));

		git_odb_object_free(odbobj);
		git_odb_free(odb);
		}
		break;
	case SHOW_NONE:
		/* just want return result */
		break;
	case SHOW_PRETTY:

		switch (git_object_type(obj)) {
		case GIT_OBJECT_BLOB:
			show_blob((const git_blob *)obj);
			break;
		case GIT_OBJECT_COMMIT:
			show_commit((const git_commit *)obj);
			break;
		case GIT_OBJECT_TREE:
			show_tree((const git_tree *)obj);
			break;
		case GIT_OBJECT_TAG:
			show_tag((const git_tag *)obj);
			break;
		default:
			printf("unknown %s\n", oidstr);
			break;
		}
		break;
	}

	git_object_free(obj);

	return 0;
}
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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int GIT_OID_HEXSZ ; 
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_type (int /*<<< orphan*/ *) ; 
 char* git_object_type2string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 char* git_reference_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_resolve (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_reference_target (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*) ; 

__attribute__((used)) static int show_ref(git_reference *ref, void *data)
{
        git_repository *repo = data;
        git_reference *resolved = NULL;
        char hex[GIT_OID_HEXSZ+1];
        const git_oid *oid;
        git_object *obj;

        if (git_reference_type(ref) == GIT_REFERENCE_SYMBOLIC)
                check_lg2(git_reference_resolve(&resolved, ref),
                          "Unable to resolve symbolic reference",
                          git_reference_name(ref));

        oid = git_reference_target(resolved ? resolved : ref);
        git_oid_fmt(hex, oid);
        hex[GIT_OID_HEXSZ] = 0;
        check_lg2(git_object_lookup(&obj, repo, oid, GIT_OBJECT_ANY),
                  "Unable to lookup object", hex);

        printf("%s %-6s\t%s\n",
               hex,
               git_object_type2string(git_object_type(obj)),
               git_reference_name(ref));

        if (resolved)
                git_reference_free(resolved);
        return 0;
}
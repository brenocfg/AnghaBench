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
typedef  int /*<<< orphan*/  oidstr ;
typedef  int /*<<< orphan*/  git_tag ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 char* git_object_type2string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_tostr (char*,int,int /*<<< orphan*/ ) ; 
 char* git_tag_message (int /*<<< orphan*/  const*) ; 
 char* git_tag_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tag_tagger (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tag_target_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tag_target_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  print_signature (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void show_tag(const git_tag *tag)
{
	char oidstr[GIT_OID_HEXSZ + 1];

	git_oid_tostr(oidstr, sizeof(oidstr), git_tag_target_id(tag));;
	printf("object %s\n", oidstr);
	printf("type %s\n", git_object_type2string(git_tag_target_type(tag)));
	printf("tag %s\n", git_tag_name(tag));
	print_signature("tagger", git_tag_tagger(tag));

	if (git_tag_message(tag))
		printf("\n%s\n", git_tag_message(tag));
}
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
struct possible_tag {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (struct possible_tag*) ; 
 int commit_name_dup (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__free (struct possible_tag*) ; 
 struct possible_tag* git__malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct possible_tag*,struct possible_tag*,int) ; 

__attribute__((used)) static int possible_tag_dup(struct possible_tag **out, struct possible_tag *in)
{
	struct possible_tag *tag;
	int error;

	tag = git__malloc(sizeof(struct possible_tag));
	GIT_ERROR_CHECK_ALLOC(tag);

	memcpy(tag, in, sizeof(struct possible_tag));
	tag->name = NULL;

	if ((error = commit_name_dup(&tag->name, in->name)) < 0) {
		git__free(tag);
		*out = NULL;
		return error;
	}

	*out = tag;
	return 0;
}
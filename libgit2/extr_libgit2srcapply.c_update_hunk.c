#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * contents; } ;
struct TYPE_9__ {TYPE_5__ lines; } ;
typedef  TYPE_1__ patch_image ;

/* Variables and functions */
 int /*<<< orphan*/  git_error_set_oom () ; 
 int /*<<< orphan*/  git_vector_get (TYPE_5__*,size_t) ; 
 int git_vector_insert_null (TYPE_5__*,size_t,size_t) ; 
 size_t git_vector_length (TYPE_5__*) ; 
 int git_vector_remove_range (TYPE_5__*,size_t,size_t) ; 

__attribute__((used)) static int update_hunk(
	patch_image *image,
	size_t linenum,
	patch_image *preimage,
	patch_image *postimage)
{
	size_t postlen = git_vector_length(&postimage->lines);
	size_t prelen = git_vector_length(&preimage->lines);
	size_t i;
	int error = 0;

	if (postlen > prelen)
		error = git_vector_insert_null(
			&image->lines, linenum, (postlen - prelen));
	else if (prelen > postlen)
		error = git_vector_remove_range(
			&image->lines, linenum, (prelen - postlen));

	if (error) {
		git_error_set_oom();
		return -1;
	}

	for (i = 0; i < git_vector_length(&postimage->lines); i++) {
		image->lines.contents[linenum + i] =
			git_vector_get(&postimage->lines, i);
	}

	return 0;
}
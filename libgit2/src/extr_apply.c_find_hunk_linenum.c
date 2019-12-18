#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lines; } ;
typedef  TYPE_1__ patch_image ;

/* Variables and functions */
 size_t git_vector_length (int /*<<< orphan*/ *) ; 
 int match_hunk (TYPE_1__*,TYPE_1__*,size_t) ; 

__attribute__((used)) static bool find_hunk_linenum(
	size_t *out,
	patch_image *image,
	patch_image *preimage,
	size_t linenum)
{
	size_t max = git_vector_length(&image->lines);
	bool match;

	if (linenum > max)
		linenum = max;

	match = match_hunk(image, preimage, linenum);

	*out = linenum;
	return match;
}
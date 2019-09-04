#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* path; int mode; } ;
typedef  TYPE_1__ git_merge_file_input ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 

__attribute__((used)) static git_merge_file_input *git_merge_file__normalize_inputs(
	git_merge_file_input *out,
	const git_merge_file_input *given)
{
	memcpy(out, given, sizeof(git_merge_file_input));

	if (!out->path)
		out->path = "file.txt";

	if (!out->mode)
		out->mode = 0100644;

	return out;
}
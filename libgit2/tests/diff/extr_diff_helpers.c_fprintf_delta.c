#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ mode; char* path; } ;
struct TYPE_5__ {scalar_t__ mode; char* path; } ;
struct TYPE_7__ {TYPE_2__ new_file; TYPE_1__ old_file; int /*<<< orphan*/  status; } ;
typedef  TYPE_3__ git_diff_delta ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char diff_pick_suffix (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,float,...) ; 
 char git_diff_status_char (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void fprintf_delta(FILE *fp, const git_diff_delta *delta, float progress)
{
	char code = git_diff_status_char(delta->status);
	char old_suffix = diff_pick_suffix(delta->old_file.mode);
	char new_suffix = diff_pick_suffix(delta->new_file.mode);

	fprintf(fp, "%c\t%s", code, delta->old_file.path);

	if ((delta->old_file.path != delta->new_file.path &&
		 strcmp(delta->old_file.path, delta->new_file.path) != 0) ||
		(delta->old_file.mode != delta->new_file.mode &&
		 delta->old_file.mode != 0 && delta->new_file.mode != 0))
		fprintf(fp, "%c %s%c", old_suffix, delta->new_file.path, new_suffix);
	else if (old_suffix != ' ')
		fprintf(fp, "%c", old_suffix);

	fprintf(fp, "\t[%.2f]\n", progress);
}
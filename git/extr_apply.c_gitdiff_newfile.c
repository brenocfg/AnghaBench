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
struct patch {int is_new; int /*<<< orphan*/  def_name; int /*<<< orphan*/  new_name; } ;
struct gitdiff_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int gitdiff_newmode (struct gitdiff_data*,char const*,struct patch*) ; 
 int /*<<< orphan*/  xstrdup_or_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gitdiff_newfile(struct gitdiff_data *state,
			   const char *line,
			   struct patch *patch)
{
	patch->is_new = 1;
	free(patch->new_name);
	patch->new_name = xstrdup_or_null(patch->def_name);
	return gitdiff_newmode(state, line, patch);
}
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
struct patch {int /*<<< orphan*/  old_name; int /*<<< orphan*/  is_new; } ;
struct apply_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_OLD_NAME ; 
 int gitdiff_verify_name (struct apply_state*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gitdiff_oldname(struct apply_state *state,
			   const char *line,
			   struct patch *patch)
{
	return gitdiff_verify_name(state, line,
				   patch->is_new, &patch->old_name,
				   DIFF_OLD_NAME);
}
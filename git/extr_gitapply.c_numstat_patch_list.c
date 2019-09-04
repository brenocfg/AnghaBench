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
struct patch {char* new_name; char* old_name; int lines_added; int lines_deleted; scalar_t__ is_binary; struct patch* next; } ;
struct apply_state {int /*<<< orphan*/  line_termination; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write_name_quoted (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void numstat_patch_list(struct apply_state *state,
			       struct patch *patch)
{
	for ( ; patch; patch = patch->next) {
		const char *name;
		name = patch->new_name ? patch->new_name : patch->old_name;
		if (patch->is_binary)
			printf("-\t-\t");
		else
			printf("%d\t%d\t", patch->lines_added, patch->lines_deleted);
		write_name_quoted(name, stdout, state->line_termination);
	}
}
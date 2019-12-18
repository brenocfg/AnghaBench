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
struct patch {struct patch* result; struct patch* new_name; struct patch* old_name; struct patch* def_name; int /*<<< orphan*/  fragments; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct patch*) ; 
 int /*<<< orphan*/  free_fragment_list (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_patch(struct patch *patch)
{
	free_fragment_list(patch->fragments);
	free(patch->def_name);
	free(patch->old_name);
	free(patch->new_name);
	free(patch->result);
	free(patch);
}
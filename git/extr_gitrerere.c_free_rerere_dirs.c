#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* status; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (TYPE_1__**) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__** rerere_dir ; 
 int rerere_dir_alloc ; 
 int rerere_dir_nr ; 

__attribute__((used)) static void free_rerere_dirs(void)
{
	int i;
	for (i = 0; i < rerere_dir_nr; i++) {
		free(rerere_dir[i]->status);
		free(rerere_dir[i]);
	}
	FREE_AND_NULL(rerere_dir);
	rerere_dir_nr = rerere_dir_alloc = 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config_iterator ;
struct TYPE_3__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ config_entries_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_entries_free (int /*<<< orphan*/ ) ; 

void config_iterator_free(git_config_iterator *iter)
{
	config_entries_iterator *it = (config_entries_iterator *) iter;
	git_config_entries_free(it->entries);
	git__free(it);
}
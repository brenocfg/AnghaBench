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
struct TYPE_4__ {struct TYPE_4__* symref_target; struct TYPE_4__* name; } ;
typedef  TYPE_1__ git_remote_head ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 

__attribute__((used)) static void free_head(git_remote_head *head)
{
	git__free(head->name);
	git__free(head->symref_target);
	git__free(head);
}
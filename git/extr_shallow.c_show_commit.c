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
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  commit_list_insert (struct commit*,void*) ; 

__attribute__((used)) static void show_commit(struct commit *commit, void *data)
{
	commit_list_insert(commit, data);
}
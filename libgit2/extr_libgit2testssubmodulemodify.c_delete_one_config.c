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
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int git_config_delete_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int delete_one_config(const git_config_entry *entry, void *payload)
{
	git_config *cfg = payload;
	return git_config_delete_entry(cfg, entry->name);
}
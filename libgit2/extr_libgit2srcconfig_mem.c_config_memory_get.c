#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config_entry ;
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_2__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ config_memory_backend ;

/* Variables and functions */
 int git_config_entries_get (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int config_memory_get(git_config_backend *backend, const char *key, git_config_entry **out)
{
	config_memory_backend *memory_backend = (config_memory_backend *) backend;
	return git_config_entries_get(out, memory_backend->entries, key);
}
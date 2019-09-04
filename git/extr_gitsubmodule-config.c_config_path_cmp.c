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
struct submodule_entry {TYPE_1__* config; } ;
struct TYPE_2__ {int /*<<< orphan*/  gitmodules_oid; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_path_cmp(const void *unused_cmp_data,
			   const void *entry,
			   const void *entry_or_key,
			   const void *unused_keydata)
{
	const struct submodule_entry *a = entry;
	const struct submodule_entry *b = entry_or_key;

	return strcmp(a->config->path, b->config->path) ||
	       !oideq(&a->config->gitmodules_oid, &b->config->gitmodules_oid);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_5__ {char* message; } ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int git_config_get_entry (TYPE_1__**,int /*<<< orphan*/ *,char const*) ; 
 TYPE_2__* git_error_last () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_get(git_config *cfg, const char *key)
{
	git_config_entry *entry;
	int error;

	if ((error = git_config_get_entry(&entry, cfg, key)) < 0) {
		if (error != GIT_ENOTFOUND)
			printf("Unable to get configuration: %s\n", git_error_last()->message);
		return 1;
	}

	puts(entry->value);
	return 0;
}
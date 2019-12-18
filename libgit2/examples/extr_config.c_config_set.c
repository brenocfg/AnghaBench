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
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_2__ {char* message; } ;

/* Variables and functions */
 scalar_t__ git_config_set_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 TYPE_1__* git_error_last () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int config_set(git_config *cfg, const char *key, const char *value)
{
	if (git_config_set_string(cfg, key, value) < 0) {
		printf("Unable to set configuration: %s\n", git_error_last()->message);
		return 1;
	}
	return 0;
}
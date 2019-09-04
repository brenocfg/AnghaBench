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

/* Variables and functions */
 int /*<<< orphan*/  discard_cache () ; 
 int /*<<< orphan*/  read_cache () ; 
 int /*<<< orphan*/  setup_git_directory () ; 
 int strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cmd__read_cache(int argc, const char **argv)
{
	int i, cnt = 1;
	if (argc == 2)
		cnt = strtol(argv[1], NULL, 0);
	setup_git_directory();
	for (i = 0; i < cnt; i++) {
		read_cache();
		discard_cache();
	}
	return 0;
}
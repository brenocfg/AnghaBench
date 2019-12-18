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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  strtoull (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_beforeafter(char *arg, uint64_t *before, uint64_t *after)
{
	char *ptr;
	char *before_str;
	char *after_str;

	ptr = strchr(optarg, ':');
	if (!ptr || !(*(ptr + 1))) {
		fprintf(stderr, "invalid input '%s'\n", arg);
		return -1;
	}
	(*ptr) = '\0';
	before_str = arg;
	after_str = ptr + 1;

	(*before) = strtoull(before_str, 0, 0);
	(*after) = strtoull(after_str, 0, 0);
	return 0;
}
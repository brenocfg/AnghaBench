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
 char* optarg ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strtoull (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_guidbeforeafter(char *arg,
				 uint64_t *guid,
				 uint64_t *before,
				 uint64_t *after)
{
	char *ptr1;
	char *ptr2;
	char *guid_str;
	char *before_str;
	char *after_str;

	ptr1 = strchr(optarg, ':');
	if (!ptr1 || !(*(ptr1 + 1))) {
		fprintf(stderr, "invalid input '%s'\n", arg);
		return -1;
	}
	guid_str = arg;
	before_str = ptr1 + 1;

	ptr2 = strchr(before_str, ':');
	if (!ptr2 || !(*(ptr2 + 1))) {
		fprintf(stderr, "invalid input '%s'\n", arg);
		return -1;
	}
	(*ptr1) = '\0';
	(*ptr2) = '\0';
	after_str = ptr2 + 1;

	(*guid) = strtoull(guid_str, 0, 0);
	(*before) = strtoull(before_str, 0, 0);
	(*after) = strtoull(after_str, 0, 0);
	return 0;
}
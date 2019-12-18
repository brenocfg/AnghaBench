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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char const*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  git_parse_ssize_t (char const*,int*) ; 

__attribute__((used)) static ssize_t get_content_length(void)
{
	ssize_t val = -1;
	const char *str = getenv("CONTENT_LENGTH");

	if (str && *str && !git_parse_ssize_t(str, &val))
		die("failed to parse CONTENT_LENGTH: %s", str);
	return val;
}
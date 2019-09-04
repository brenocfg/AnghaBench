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
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ git__strntol32 (scalar_t__*,char const*,int /*<<< orphan*/ ,char const**,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int try_parse_numeric(int *n, const char *curly_braces_content)
{
	int32_t content;
	const char *end_ptr;

	if (git__strntol32(&content, curly_braces_content, strlen(curly_braces_content),
			   &end_ptr, 10) < 0)
		return -1;

	if (*end_ptr != '\0')
		return -1;

	*n = (int)content;
	return 0;
}
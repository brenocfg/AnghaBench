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
 int /*<<< orphan*/  strlcat (char*,char const*,size_t) ; 

__attribute__((used)) static void
appendstr(
	char *string,
	size_t s,
	const char *new
	)
{
	if (*string != '\0') {
		(void)strlcat(string, ",", s);
	}
	(void)strlcat(string, new, s);

	return;
}
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
 unsigned long ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * forbidden_custom_headers ; 
 size_t http_header_name_length (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static bool is_forbidden_custom_header(const char *custom_header)
{
	unsigned long i;
	size_t name_len = http_header_name_length(custom_header);

	/* Disallow headers that we set */
	for (i = 0; i < ARRAY_SIZE(forbidden_custom_headers); i++)
		if (strncmp(forbidden_custom_headers[i], custom_header, name_len) == 0)
			return true;

	return false;
}
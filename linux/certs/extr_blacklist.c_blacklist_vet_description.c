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
 int EINVAL ; 
 int /*<<< orphan*/  isxdigit (char const) ; 

__attribute__((used)) static int blacklist_vet_description(const char *desc)
{
	int n = 0;

	if (*desc == ':')
		return -EINVAL;
	for (; *desc; desc++)
		if (*desc == ':')
			goto found_colon;
	return -EINVAL;

found_colon:
	desc++;
	for (; *desc; desc++) {
		if (!isxdigit(*desc))
			return -EINVAL;
		n++;
	}

	if (n == 0 || n & 1)
		return -EINVAL;
	return 0;
}
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
 int N_INJ_TYPES ; 
 int /*<<< orphan*/ * flags_options ; 
 int inj_type ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __set_inj(const char *buf)
{
	int i;

	for (i = 0; i < N_INJ_TYPES; i++) {
		if (!strncmp(flags_options[i], buf, strlen(flags_options[i]))) {
			inj_type = i;
			return 0;
		}
	}
	return -EINVAL;
}
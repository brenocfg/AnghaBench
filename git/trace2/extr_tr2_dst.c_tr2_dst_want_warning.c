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
 int /*<<< orphan*/  TR2_SYSENV_DST_DEBUG ; 
 scalar_t__ atoi (char const*) ; 
 char* tr2_sysenv_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tr2_dst_want_warning(void)
{
	static int tr2env_dst_debug = -1;

	if (tr2env_dst_debug == -1) {
		const char *env_value = tr2_sysenv_get(TR2_SYSENV_DST_DEBUG);
		if (!env_value || !*env_value)
			tr2env_dst_debug = 0;
		else
			tr2env_dst_debug = atoi(env_value) > 0;
	}

	return tr2env_dst_debug;
}
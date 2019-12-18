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
 int /*<<< orphan*/  BHND_NV_LOG (char*,char,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  BHND_NV_PRINT_WIDTH (size_t) ; 
 int EINVAL ; 
 char* memchr (char const*,char,size_t) ; 

int
bhnd_nvram_parse_env(const char *env, size_t env_len, char delim,
    const char **name, size_t *name_len, const char **value, size_t *value_len)
{
	const char *p;

	/* Name */
	if ((p = memchr(env, delim, env_len)) == NULL) {
		BHND_NV_LOG("delimiter '%c' not found in '%.*s'\n", delim,
		    BHND_NV_PRINT_WIDTH(env_len), env);
		return (EINVAL);
	}

	/* Name */
	if (name != NULL)
		*name = env;
	if (name_len != NULL)
		*name_len = p - env;

	/* Skip delim */
	p++;

	/* Value */
	if (value != NULL)
		*value = p;
	if (value_len != NULL)
		*value_len = env_len - (p - env);

	return (0);
}
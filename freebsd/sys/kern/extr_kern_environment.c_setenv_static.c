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
 int md_env_len ; 
 int md_env_pos ; 
 char* md_envp ; 
 int sprintf (char*,char*,char const*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
setenv_static(const char *name, const char *value)
{
	int len;

	if (md_env_pos >= md_env_len)
		return (-1);

	/* Check space for x=y and two nuls */
	len = strlen(name) + strlen(value);
	if (len + 3 < md_env_len - md_env_pos) {
		len = sprintf(&md_envp[md_env_pos], "%s=%s", name, value);
		md_env_pos += len+1;
		md_envp[md_env_pos] = '\0';
		return (0);
	} else
		return (-1);

}
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
 int /*<<< orphan*/  os_strlcpy (char*,char const*,int) ; 
 int os_strlen (char*) ; 

__attribute__((used)) static int tls_passwd_cb(char *buf, int size, int rwflag, void *password)
{
	if (!password)
		return 0;
	os_strlcpy(buf, (const char *) password, size);
	return os_strlen(buf);
}
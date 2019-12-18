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
 int /*<<< orphan*/  M_SMBSTR ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bcopy (char const*,char*,size_t) ; 
 char* malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

char *
smb_strdup(const char *s)
{
	char *p;
	size_t len;

	len = s ? strlen(s) + 1 : 1;
	p = malloc(len, M_SMBSTR, M_WAITOK);
	if (s)
		bcopy(s, p, len);
	else
		*p = 0;
	return p;
}
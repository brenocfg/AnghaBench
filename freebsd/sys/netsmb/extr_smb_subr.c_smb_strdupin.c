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
 int copyinstr (char*,char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *
smb_strdupin(char *s, size_t maxlen)
{
	char *p;
	int error;

	p = malloc(maxlen + 1, M_SMBSTR, M_WAITOK);
	error = copyinstr(s, p, maxlen + 1, NULL);
	if (error) {
		free(p, M_SMBSTR);
		return (NULL);
	}
	return p;
}
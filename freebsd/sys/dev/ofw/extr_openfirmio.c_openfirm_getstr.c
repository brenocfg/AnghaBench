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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ OFIOCMAXNAME ; 
 int copyin (char const*,char*,int) ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
openfirm_getstr(int len, const char *user, char **cpp)
{
	int error;
	char *cp;

	/* Reject obvious bogus requests. */
	if ((u_int)len > OFIOCMAXNAME)
		return (ENAMETOOLONG);

	*cpp = cp = malloc(len + 1, M_TEMP, M_WAITOK);
	error = copyin(user, cp, len);
	cp[len] = '\0';
	return (error);
}
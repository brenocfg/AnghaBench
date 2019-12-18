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
struct passwd {char* pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  L_cuserid ; 
 int /*<<< orphan*/  geteuid () ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int /*<<< orphan*/ ) ; 

char *
cuserid(char *s)
{
	struct passwd *pwd;

	if ((pwd = getpwuid(geteuid())) == NULL) {
		if (s)
			*s = '\0';
		return (s);
	}
	if (s) {
		(void)strncpy(s, pwd->pw_name, L_cuserid);
		return (s);
	}
	return (pwd->pw_name);
}
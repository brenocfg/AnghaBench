#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* strmod_linkinfo; } ;

/* Variables and functions */
 int mod_install (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modlinkage ; 
 TYPE_1__ modlstrmod ; 
 char* rcsid ; 
 int /*<<< orphan*/  strlcpy (char*,char*,unsigned int) ; 
 int strlen (char*) ; 

int
_init(
     void
     )
{
	static char revision[] = "4.6";
	char *s, *S;
	char *t;

#ifndef lint
	t = rcsid;
#endif

	/*
	 * copy RCS revision into Drv_name
	 *
	 * are we forcing RCS here to do things it was not built for ?
	 */
	s = revision;
	if (*s == '$')
	{
		/*
		 * skip "$Revision: "
		 * if present. - not necessary on a -kv co (cvs export)
		 */
		while (*s && (*s != ' '))
		{
			s++;
		}
		if (*s == ' ') s++;
	}

	t = modlstrmod.strmod_linkinfo;
	while (*t && (*t != ' '))
	{
		t++;
	}
	if (*t == ' ') t++;

	S = s;
	while (*S && (((*S >= '0') && (*S <= '9')) || (*S == '.')))
	{
		S++;
	}

	if (*s && *t && (S > s))
	{
		if (strlen(t) >= (S - s))
		{
			strlcpy(t, s, (unsigned)(S - s));
		}
	}
	return (mod_install(&modlinkage));
}
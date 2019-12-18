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
 int CONTENTS_LAVA ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_SOLID ; 
 int CONTENTS_WATER ; 
 int /*<<< orphan*/  Q_strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  Q_strncasecmp (char*,char*,int) ; 

int Q1_TextureContents(char *name)
{
	if (!Q_strcasecmp(name, "clip")) return CONTENTS_SOLID;
	if (name[0] == '*')
	{
		if (!Q_strncasecmp(name+1,"lava",4)) return CONTENTS_LAVA;
		else if (!Q_strncasecmp(name+1,"slime",5)) return CONTENTS_SLIME;
		else return CONTENTS_WATER;
	} //end if
	else if (!Q_strncasecmp(name, "sky", 3)) return CONTENTS_SOLID;
	else return CONTENTS_SOLID;
}
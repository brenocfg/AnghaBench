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
#define  ARR 137 
#define  CON 136 
#define  CONVC 135 
#define  CONVO 134 
#define  DONTFREE 133 
#define  FCN 132 
#define  FLD 131 
#define  NUM 130 
#define  REC 129 
#define  STR 128 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

const char *flags2str(int flags)
{
	static const struct ftab {
		const char *name;
		int value;
	} flagtab[] = {
		{ "NUM", NUM },
		{ "STR", STR },
		{ "DONTFREE", DONTFREE },
		{ "CON", CON },
		{ "ARR", ARR },
		{ "FCN", FCN },
		{ "FLD", FLD },
		{ "REC", REC },
		{ "CONVC", CONVC },
		{ "CONVO", CONVO },
		{ NULL, 0 }
	};
	static char buf[100];
	int i;
	char *cp = buf;

	for (i = 0; flagtab[i].name != NULL; i++) {
		if ((flags & flagtab[i].value) != 0) {
			if (cp > buf)
				*cp++ = '|';
			strcpy(cp, flagtab[i].name);
			cp += strlen(cp);
		}
	}

	return buf;
}
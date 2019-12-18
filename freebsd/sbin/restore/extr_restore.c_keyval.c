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
 int INOFND ; 
 int MODECHG ; 
 int NAMEFND ; 
 int ONTAPE ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *
keyval(int key)
{
	static char keybuf[32];

	(void) strcpy(keybuf, "|NIL");
	keybuf[0] = '\0';
	if (key & ONTAPE)
		(void) strcat(keybuf, "|ONTAPE");
	if (key & INOFND)
		(void) strcat(keybuf, "|INOFND");
	if (key & NAMEFND)
		(void) strcat(keybuf, "|NAMEFND");
	if (key & MODECHG)
		(void) strcat(keybuf, "|MODECHG");
	return (&keybuf[1]);
}
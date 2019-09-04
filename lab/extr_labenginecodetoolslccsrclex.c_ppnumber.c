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
 int DIGIT ; 
 int LETTER ; 
 size_t* cp ; 
 int /*<<< orphan*/  error (char*,int,char*,char*) ; 
 int* map ; 
 int token ; 

__attribute__((used)) static void ppnumber(char *which) {
	unsigned char *rcp = cp--;

	for ( ; (map[*cp]&(DIGIT|LETTER)) || *cp == '.'; cp++)
		if ((cp[0] == 'E' || cp[0] == 'e')
		&&  (cp[1] == '-' || cp[1] == '+'))
			cp++;
	if (cp > rcp)
		error("`%S' is a preprocessing number but an invalid %s constant\n", token,

			(char*)cp-token, which);
}
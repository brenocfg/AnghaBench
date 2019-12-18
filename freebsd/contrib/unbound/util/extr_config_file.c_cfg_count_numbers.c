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
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 

int 
cfg_count_numbers(const char* s)
{
	/* format ::= (sp num)+ sp  */
	/* num ::= [-](0-9)+        */
	/* sp ::= (space|tab)*      */
	int num = 0;
	while(*s) {
		while(*s && isspace((unsigned char)*s))
			s++;
		if(!*s) /* end of string */
			break;
		if(*s == '-')
			s++;
		if(!*s) /* only - not allowed */
			return 0;
		if(!isdigit((unsigned char)*s)) /* bad character */
			return 0;
		while(*s && isdigit((unsigned char)*s))
			s++;
		num++;
	}
	return num;
}
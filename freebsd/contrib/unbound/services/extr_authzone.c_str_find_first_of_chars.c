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
 char* strchr (char*,char) ; 

__attribute__((used)) static char*
str_find_first_of_chars(char* s, char a, char b)
{
	char* ra = strchr(s, a);
	char* rb = strchr(s, b);
	if(!ra) return rb;
	if(!rb) return ra;
	if(ra < rb) return ra;
	return rb;
}
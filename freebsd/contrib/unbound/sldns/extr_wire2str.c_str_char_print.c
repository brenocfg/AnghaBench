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
typedef  char uint8_t ;

/* Variables and functions */
 scalar_t__ isprint (unsigned char) ; 
 int sldns_str_print (char**,size_t*,char*,unsigned int) ; 

__attribute__((used)) static int str_char_print(char** s, size_t* sl, uint8_t c)
{
	if(isprint((unsigned char)c) || c == '\t') {
		if(c == '\"' || c == '\\')
			return sldns_str_print(s, sl, "\\%c", c);
		if(*sl) {
			**s = (char)c;
			(*s)++;
			(*sl)--;
		}
		return 1;
	}
	return sldns_str_print(s, sl, "\\%03u", (unsigned)c);
}
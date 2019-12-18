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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 size_t strlen (char*) ; 
 char tolower (unsigned char) ; 

int
dname_lab_startswith(uint8_t* label, char* prefix, char** endptr)
{
	size_t plen = strlen(prefix);
	size_t orig_plen = plen;
	size_t lablen = (size_t)*label;
	if(plen > lablen)
		return 0;
	label++;
	while(plen--) {
		if(*prefix != tolower((unsigned char)*label)) {
			return 0;
		}
		prefix++; label++;
	}
	if(orig_plen < lablen)
		*endptr = (char *)label;
	else
		/* prefix length == label length */
		*endptr = NULL;
	return 1;
}
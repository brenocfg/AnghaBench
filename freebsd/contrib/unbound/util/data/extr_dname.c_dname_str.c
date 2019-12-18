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
 int LDNS_MAX_DOMAINLEN ; 
 scalar_t__ LDNS_MAX_LABELLEN ; 
 scalar_t__ isalnum (unsigned char) ; 

void dname_str(uint8_t* dname, char* str)
{
	size_t len = 0;
	uint8_t lablen = 0;
	char* s = str;
	if(!dname || !*dname) {
		*s++ = '.';
		*s = 0;
		return;
	}
	lablen = *dname++;
	while(lablen) {
		if(lablen > LDNS_MAX_LABELLEN) {
			*s++ = '#';
			*s = 0;
			return;
		}
		len += lablen+1;
		if(len >= LDNS_MAX_DOMAINLEN-1) {
			*s++ = '&';
			*s = 0;
			return;
		}
		while(lablen--) {
			if(isalnum((unsigned char)*dname) 
				|| *dname == '-' || *dname == '_' 
				|| *dname == '*')
				*s++ = *(char*)dname++;
			else	{
				*s++ = '?';
				dname++;
			}
		}
		*s++ = '.';
		lablen = *dname++;
	}
	*s = 0;
}
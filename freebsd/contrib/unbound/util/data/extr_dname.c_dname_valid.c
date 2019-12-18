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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 size_t LDNS_MAX_DOMAINLEN ; 

size_t 
dname_valid(uint8_t* dname, size_t maxlen)
{
	size_t len = 0;
	size_t labellen;
	labellen = *dname++;
	while(labellen) {
		if(labellen&0xc0)
			return 0; /* no compression ptrs allowed */
		len += labellen + 1;
		if(len >= LDNS_MAX_DOMAINLEN)
			return 0; /* too long */
		if(len > maxlen)
			return 0; /* does not fit in memory allocation */
		dname += labellen;
		labellen = *dname++;
	}
	len += 1;
	if(len > maxlen)
		return 0; /* does not fit in memory allocation */
	return len;
}
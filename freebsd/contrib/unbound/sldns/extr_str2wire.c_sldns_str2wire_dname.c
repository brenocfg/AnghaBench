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
typedef  int /*<<< orphan*/  dname ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_DOMAINLEN ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/ * memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ sldns_str2wire_dname_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 

uint8_t* sldns_str2wire_dname(const char* str, size_t* len)
{
	uint8_t dname[LDNS_MAX_DOMAINLEN+1];
	*len = sizeof(dname);
	if(sldns_str2wire_dname_buf(str, dname, len) == 0) {
		uint8_t* r = (uint8_t*)malloc(*len);
		if(r) return memcpy(r, dname, *len);
	}
	*len = 0;
	return NULL;
}
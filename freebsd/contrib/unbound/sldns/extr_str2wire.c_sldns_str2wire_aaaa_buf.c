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
 int /*<<< orphan*/  AF_INET6 ; 
 int LDNS_IP6ADDRLEN ; 
 int LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL ; 
 int LDNS_WIREPARSE_ERR_NOT_IMPL ; 
 int LDNS_WIREPARSE_ERR_OK ; 
 int LDNS_WIREPARSE_ERR_SYNTAX_IP6 ; 
 int inet_pton (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int sldns_str2wire_aaaa_buf(const char* str, uint8_t* rd, size_t* len)
{
#ifdef AF_INET6
	uint8_t address[LDNS_IP6ADDRLEN + 1];
	if(inet_pton(AF_INET6, (char*)str, address) != 1)
		return LDNS_WIREPARSE_ERR_SYNTAX_IP6;
	if(*len < LDNS_IP6ADDRLEN)
		return LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL;
	memmove(rd, address, LDNS_IP6ADDRLEN);
	*len = LDNS_IP6ADDRLEN;
	return LDNS_WIREPARSE_ERR_OK;
#else
	return LDNS_WIREPARSE_ERR_NOT_IMPL;
#endif
}
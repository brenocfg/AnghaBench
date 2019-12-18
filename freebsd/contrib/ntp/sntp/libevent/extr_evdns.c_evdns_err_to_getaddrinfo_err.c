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
 int DNS_ERR_NONE ; 
 int DNS_ERR_NOTEXIST ; 
 int EVUTIL_EAI_FAIL ; 
 int EVUTIL_EAI_NONAME ; 

__attribute__((used)) static int
evdns_err_to_getaddrinfo_err(int e1)
{
	/* XXX Do this better! */
	if (e1 == DNS_ERR_NONE)
		return 0;
	else if (e1 == DNS_ERR_NOTEXIST)
		return EVUTIL_EAI_NONAME;
	else
		return EVUTIL_EAI_FAIL;
}
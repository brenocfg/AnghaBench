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
#define  REFID_HASH 129 
#define  REFID_IPV4 128 
 int drefid ; 

__attribute__((used)) static const char *
showdrefid2str(void)
{
	switch (drefid) {
	    case REFID_HASH:
	    	return "hash";
	    case REFID_IPV4:
	    	return "ipv4";
	    default:
	    	return "Unknown";
	}
}
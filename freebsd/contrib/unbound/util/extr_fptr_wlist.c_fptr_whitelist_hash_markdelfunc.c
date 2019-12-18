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
typedef  int /*<<< orphan*/ * lruhash_markdelfunc_type ;

/* Variables and functions */
 int /*<<< orphan*/  rrset_markdel ; 
 int /*<<< orphan*/  subnet_markdel ; 

int 
fptr_whitelist_hash_markdelfunc(lruhash_markdelfunc_type fptr)
{
	if(fptr == NULL) return 1;
	else if(fptr == &rrset_markdel) return 1;
#ifdef CLIENT_SUBNET
	else if(fptr == &subnet_markdel) return 1;
#endif
	return 0;
}
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
 size_t EIPSEC_MAX ; 
 size_t __ipsec_errcode ; 
 char const** ipsec_errlist ; 

const char *ipsec_strerror(void)
{
	if (__ipsec_errcode < 0 || __ipsec_errcode > EIPSEC_MAX)
		__ipsec_errcode = EIPSEC_MAX;

	return ipsec_errlist[__ipsec_errcode];
}
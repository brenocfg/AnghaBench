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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ TLS_TCB_SIZE ; 
 scalar_t__ TLS_TP_OFFSET ; 

void *
_mips_get_tls(void)
{
	uint32_t _rv;

	__asm__ __volatile__ (
	    ".set\tpush\n\t"
	    ".set\tmips32r2\n\t"
	    "rdhwr\t%0, $29\n\t"
	    ".set\tpop"
	    : "=r" (_rv));
	/*
	 * XXXSS See 'git show c6be4f4d2d1b71c04de5d3bbb6933ce2dbcdb317'
	 *
	 * Remove the offset since this really a request to get the TLS
	 * pointer via sysarch() (in theory).  Of course, this may go away
	 * once the TLS code is rewritten.
	 */
	_rv = _rv - TLS_TP_OFFSET - TLS_TCB_SIZE;

	return (void *)_rv;
}
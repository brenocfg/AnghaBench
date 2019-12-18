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
typedef  long long u_quad_t ;
struct bintime {long long frac; scalar_t__ sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  getbinuptime (struct bintime*) ; 

u_quad_t
init_va_filerev(void)
{
	struct bintime bt;

	getbinuptime(&bt);
	return (((u_quad_t)bt.sec << 32LL) | (bt.frac >> 32LL));
}
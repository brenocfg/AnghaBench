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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int rump_sys__ksem_open (char const*,int,int /*<<< orphan*/ ,unsigned int,intptr_t*) ; 

int _ksem_open(const char *a, int b, mode_t c, unsigned int d, intptr_t *e)
    {return rump_sys__ksem_open(a,b,c,d,e);}
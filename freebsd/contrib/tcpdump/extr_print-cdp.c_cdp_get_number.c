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
typedef  unsigned long u_char ;

/* Variables and functions */

__attribute__((used)) static unsigned long cdp_get_number(const u_char * p, int l)
{
    unsigned long res=0;
    while( l>0 )
    {
	res = (res<<8) + *p;
	p++; l--;
    }
    return res;
}
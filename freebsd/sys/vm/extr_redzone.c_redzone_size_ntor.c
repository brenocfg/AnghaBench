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
typedef  scalar_t__ u_long ;

/* Variables and functions */
 scalar_t__ REDZONE_FSIZE ; 
 scalar_t__ redzone_roundup (scalar_t__) ; 

u_long
redzone_size_ntor(u_long nsize)
{

	return (nsize + redzone_roundup(nsize) + REDZONE_FSIZE);
}
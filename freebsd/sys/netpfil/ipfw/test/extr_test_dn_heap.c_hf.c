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
typedef  char uint32_t ;
struct x {char* buf; } ;

/* Variables and functions */
 int DNHT_KEY_IS_OBJ ; 

uint32_t hf(uintptr_t key, int flags, void *arg)
{
	return (flags & DNHT_KEY_IS_OBJ) ?
		((struct x *)key)->buf[0] : *(char *)key;
}
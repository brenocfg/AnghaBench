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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  forced_memzero_val ; 
 int /*<<< orphan*/  memset_func (void*,int /*<<< orphan*/ ,size_t) ; 

void forced_memzero(void *ptr, size_t len)
{
	memset_func(ptr, 0, len);
	if (len)
		forced_memzero_val = ((u8 *) ptr)[0];
}
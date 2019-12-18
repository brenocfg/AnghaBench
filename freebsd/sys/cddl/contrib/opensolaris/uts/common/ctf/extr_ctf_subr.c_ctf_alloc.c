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
 int KM_NOWAIT ; 
 int KM_TMP ; 
 void* kobj_alloc (size_t,int) ; 

void *
ctf_alloc(size_t size)
{
	return (kobj_alloc(size, KM_NOWAIT|KM_TMP));
}
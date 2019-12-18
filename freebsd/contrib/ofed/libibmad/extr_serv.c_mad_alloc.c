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
 scalar_t__ IB_MAD_SIZE ; 
 void* umad_alloc (int,scalar_t__) ; 
 scalar_t__ umad_size () ; 

void *mad_alloc(void)
{
	return umad_alloc(1, umad_size() + IB_MAD_SIZE);
}
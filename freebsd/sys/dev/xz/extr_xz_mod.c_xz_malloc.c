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
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  XZ_DEC ; 
 void* malloc (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *
xz_malloc(unsigned long size)
{
	void *addr;

	addr = malloc(size, XZ_DEC, M_NOWAIT);
	return (addr);
}
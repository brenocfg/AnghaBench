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
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_QLNXBUF ; 
 int /*<<< orphan*/  bzero (scalar_t__,scalar_t__) ; 
 scalar_t__ malloc (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *
qlnx_zalloc(uint32_t size)
{
	caddr_t	va;

	va = malloc((unsigned long)size, M_QLNXBUF, M_NOWAIT);
	bzero(va, size);
	return ((void *)va);
}
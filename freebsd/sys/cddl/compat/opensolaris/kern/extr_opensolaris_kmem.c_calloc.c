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
 int /*<<< orphan*/  KM_NOSLEEP ; 
 void* kmem_zalloc (size_t,int /*<<< orphan*/ ) ; 

void *
calloc(size_t n, size_t s)
{
	return (kmem_zalloc(n * s, KM_NOSLEEP));
}
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
typedef  int /*<<< orphan*/  vm_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  UMA_ANYDOMAIN ; 
 void* uma_large_malloc_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void *
uma_large_malloc(vm_size_t size, int wait)
{

	return uma_large_malloc_domain(size, UMA_ANYDOMAIN, wait);
}
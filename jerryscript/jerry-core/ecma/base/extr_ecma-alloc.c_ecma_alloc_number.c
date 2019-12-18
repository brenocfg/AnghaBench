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
typedef  int /*<<< orphan*/  ecma_number_t ;

/* Variables and functions */
 scalar_t__ jmem_pools_alloc (int) ; 

ecma_number_t *
ecma_alloc_number (void)
{
  return (ecma_number_t *) jmem_pools_alloc (sizeof (ecma_number_t));
}
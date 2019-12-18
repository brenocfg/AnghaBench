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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_bitmap_t ;

/* Variables and functions */
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_OCS ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bitstr_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

ocs_bitmap_t *
ocs_bitmap_alloc(uint32_t n_bits)
{

	return malloc(bitstr_size(n_bits), M_OCS, M_ZERO | M_NOWAIT);
}
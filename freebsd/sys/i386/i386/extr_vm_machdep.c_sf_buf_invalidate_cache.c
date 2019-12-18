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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  sf_buf_invalidate ; 
 int /*<<< orphan*/  sf_buf_process_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
sf_buf_invalidate_cache(vm_page_t m)
{

	return (sf_buf_process_page(m, sf_buf_invalidate));
}
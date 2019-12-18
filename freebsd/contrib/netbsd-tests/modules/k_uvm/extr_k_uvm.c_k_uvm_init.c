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
typedef  int /*<<< orphan*/  prop_dictionary_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  clogp ; 
 int /*<<< orphan*/  page_size ; 
 int /*<<< orphan*/  sysctl_k_uvm_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int
k_uvm_init(prop_dictionary_t props)
{

	page_size = PAGE_SIZE;

	sysctl_k_uvm_setup(&clogp);

	return 0;
}
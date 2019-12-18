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
struct ppc64_opd_entry {int dummy; } ;
typedef  struct ppc64_opd_entry func_desc_t ;

/* Variables and functions */

__attribute__((used)) static func_desc_t func_desc(unsigned long addr)
{
	return *(struct ppc64_opd_entry *)addr;
}
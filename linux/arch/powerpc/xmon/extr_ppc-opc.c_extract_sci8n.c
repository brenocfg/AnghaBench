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
typedef  int /*<<< orphan*/  ppc_cpu_t ;

/* Variables and functions */
 long extract_sci8 (unsigned long,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static long
extract_sci8n (unsigned long insn,
	       ppc_cpu_t dialect,
	       int *invalid)
{
  return -extract_sci8 (insn, dialect, invalid);
}
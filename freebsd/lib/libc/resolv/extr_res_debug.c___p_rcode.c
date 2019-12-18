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
 int /*<<< orphan*/  __p_rcode_syms ; 
 char const* sym_ntos (int /*<<< orphan*/ ,int,int*) ; 

const char *
p_rcode(int rcode) {
	return (sym_ntos(__p_rcode_syms, rcode, (int *)0));
}
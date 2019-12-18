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
typedef  int /*<<< orphan*/  xo_xsf_flags_t ;
typedef  int xo_xof_flags_t ;

/* Variables and functions */
 int XOF_DTRT ; 
 int /*<<< orphan*/  XSF_DTRT ; 

__attribute__((used)) static xo_xsf_flags_t
xo_stack_flags (xo_xof_flags_t xflags)
{
    if (xflags & XOF_DTRT)
	return XSF_DTRT;
    return 0;
}
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
typedef  int /*<<< orphan*/  func_ptr ;

/* Variables and functions */
 int /*<<< orphan*/  const* jcr_ptr ; 
 int jcr_run ; 

void
_Jv_RegisterClasses(const func_ptr *jcr)
{

	jcr_run = 1;
	jcr_ptr = jcr;
}
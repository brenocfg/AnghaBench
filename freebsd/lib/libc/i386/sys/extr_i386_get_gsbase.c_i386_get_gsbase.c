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
 int /*<<< orphan*/  I386_GET_GSBASE ; 
 int sysarch (int /*<<< orphan*/ ,void**) ; 

int
i386_get_gsbase(void **addr)
{

	return (sysarch(I386_GET_GSBASE, addr));
}
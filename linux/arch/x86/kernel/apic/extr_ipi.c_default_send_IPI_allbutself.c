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
 int /*<<< orphan*/  APIC_DEST_ALLBUT ; 
 int /*<<< orphan*/  __default_send_IPI_shortcut (int /*<<< orphan*/ ,int) ; 

void default_send_IPI_allbutself(int vector)
{
	__default_send_IPI_shortcut(APIC_DEST_ALLBUT, vector);
}
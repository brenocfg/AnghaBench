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
 int MAX_VM ; 
 int /*<<< orphan*/  VM_Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmTable ; 

void VM_Clear(void) {
	int i;
	for (i=0;i<MAX_VM; i++) {
		VM_Free(&vmTable[i]);
	}
}
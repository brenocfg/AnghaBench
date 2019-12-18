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
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pseudo_lock_class ; 
 scalar_t__ pseudo_lock_major ; 
 int /*<<< orphan*/  unregister_chrdev (scalar_t__,char*) ; 

void rdt_pseudo_lock_release(void)
{
	class_destroy(pseudo_lock_class);
	pseudo_lock_class = NULL;
	unregister_chrdev(pseudo_lock_major, "pseudo_lock");
	pseudo_lock_major = 0;
}
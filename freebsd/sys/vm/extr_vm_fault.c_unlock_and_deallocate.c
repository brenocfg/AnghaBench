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
struct faultstate {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fault_deallocate (struct faultstate*) ; 

__attribute__((used)) static void
unlock_and_deallocate(struct faultstate *fs)
{

	VM_OBJECT_WUNLOCK(fs->object);
	fault_deallocate(fs);
}
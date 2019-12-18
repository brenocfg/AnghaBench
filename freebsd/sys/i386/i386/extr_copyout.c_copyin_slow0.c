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
typedef  scalar_t__ vm_offset_t ;
struct copyin_arg0 {int /*<<< orphan*/  len; scalar_t__ kc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
copyin_slow0(vm_offset_t kva, void *arg)
{
	struct copyin_arg0 *ca;

	ca = arg;
	bcopy((void *)kva, (void *)ca->kc, ca->len);
}
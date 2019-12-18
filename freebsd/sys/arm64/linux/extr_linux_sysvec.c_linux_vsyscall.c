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
struct thread {int dummy; } ;

/* Variables and functions */
 int EDOOFUS ; 
 int /*<<< orphan*/  LIN_SDT_PROBE0 (int /*<<< orphan*/ ,int (*) (struct thread*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysvec ; 
 int /*<<< orphan*/  todo ; 

__attribute__((used)) static int
linux_vsyscall(struct thread *td)
{

	/* LINUXTODO: implement */
	LIN_SDT_PROBE0(sysvec, linux_vsyscall, todo);
	return (EDOOFUS);
}
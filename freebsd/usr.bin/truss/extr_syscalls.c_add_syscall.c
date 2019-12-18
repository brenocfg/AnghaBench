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
typedef  size_t u_int ;
struct syscall {int dummy; } ;
struct procabi {int /*<<< orphan*/  extra_syscalls; struct syscall** syscalls; } ;
struct extra_syscall {size_t number; struct syscall* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct extra_syscall*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 struct extra_syscall* malloc (int) ; 
 size_t nitems (struct syscall**) ; 

__attribute__((used)) static void
add_syscall(struct procabi *abi, u_int number, struct syscall *sc)
{
	struct extra_syscall *es;

	if (number < nitems(abi->syscalls)) {
		assert(abi->syscalls[number] == NULL);
		abi->syscalls[number] = sc;
	} else {
		es = malloc(sizeof(*es));
		es->sc = sc;
		es->number = number;
		STAILQ_INSERT_TAIL(&abi->extra_syscalls, es, entries);
	}
}
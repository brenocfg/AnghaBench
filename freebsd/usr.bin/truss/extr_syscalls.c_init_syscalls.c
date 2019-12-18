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
struct syscall {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct syscall*,int /*<<< orphan*/ ) ; 
 struct syscall* decoded_syscalls ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  quad_fixup (struct syscall*) ; 
 int /*<<< orphan*/  syscalls ; 

void
init_syscalls(void)
{
	struct syscall *sc;

	STAILQ_INIT(&syscalls);
	for (sc = decoded_syscalls; sc->name != NULL; sc++) {
#ifndef __LP64__
		quad_fixup(sc);
#endif
		STAILQ_INSERT_HEAD(&syscalls, sc, entries);
	}
}
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
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 scalar_t__ allocate_module_tls (int) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  lock_release (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  rtld_bind_lock ; 
 scalar_t__ tls_dtv_generation ; 
 int tls_max_index ; 
 int /*<<< orphan*/  wlock_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__* xcalloc (int,int) ; 

__attribute__((used)) static void *
tls_get_addr_slow(Elf_Addr **dtvp, int index, size_t offset)
{
    Elf_Addr *newdtv, *dtv;
    RtldLockState lockstate;
    int to_copy;

    dtv = *dtvp;
    /* Check dtv generation in case new modules have arrived */
    if (dtv[0] != tls_dtv_generation) {
	wlock_acquire(rtld_bind_lock, &lockstate);
	newdtv = xcalloc(tls_max_index + 2, sizeof(Elf_Addr));
	to_copy = dtv[1];
	if (to_copy > tls_max_index)
	    to_copy = tls_max_index;
	memcpy(&newdtv[2], &dtv[2], to_copy * sizeof(Elf_Addr));
	newdtv[0] = tls_dtv_generation;
	newdtv[1] = tls_max_index;
	free(dtv);
	lock_release(rtld_bind_lock, &lockstate);
	dtv = *dtvp = newdtv;
    }

    /* Dynamically allocate module TLS if necessary */
    if (dtv[index + 1] == 0) {
	/* Signal safe, wlock will block out signals. */
	wlock_acquire(rtld_bind_lock, &lockstate);
	if (!dtv[index + 1])
	    dtv[index + 1] = (Elf_Addr)allocate_module_tls(index);
	lock_release(rtld_bind_lock, &lockstate);
    }
    return ((void *)(dtv[index + 1] + offset));
}
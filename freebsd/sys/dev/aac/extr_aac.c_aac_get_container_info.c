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
struct aac_softc {int flags; int /*<<< orphan*/  aac_dev; } ;
struct aac_mntinforesp {int dummy; } ;
struct aac_mntinfo {int MntCount; int /*<<< orphan*/  MntType; int /*<<< orphan*/  Command; } ;
struct aac_fib {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int AAC_FLAGS_LBA_64BIT ; 
 int /*<<< orphan*/  ContainerCommand ; 
 int /*<<< orphan*/  FT_FILESYS ; 
 int /*<<< orphan*/  VM_NameServe ; 
 int /*<<< orphan*/  VM_NameServe64 ; 
 scalar_t__ aac_sync_fib (struct aac_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aac_fib*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct aac_mntinforesp *
aac_get_container_info(struct aac_softc *sc, struct aac_fib *fib, int cid)
{
	struct aac_mntinfo *mi;

	mi = (struct aac_mntinfo *)&fib->data[0];
	/* use 64-bit LBA if enabled */
	mi->Command = (sc->flags & AAC_FLAGS_LBA_64BIT) ?
	    VM_NameServe64 : VM_NameServe;
	mi->MntType = FT_FILESYS;
	mi->MntCount = cid;

	if (aac_sync_fib(sc, ContainerCommand, 0, fib,
			 sizeof(struct aac_mntinfo))) {
		device_printf(sc->aac_dev, "Error probing container %d\n", cid);
		return (NULL);
	}

	return ((struct aac_mntinforesp *)&fib->data[0]);
}
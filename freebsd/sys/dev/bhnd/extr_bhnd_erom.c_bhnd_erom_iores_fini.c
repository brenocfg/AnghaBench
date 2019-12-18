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
struct bhnd_erom_iores {int mapped_rid; int /*<<< orphan*/ * mapped; int /*<<< orphan*/  owner; } ;
struct bhnd_erom_io {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bhnd_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct bhnd_erom_io*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bhnd_erom_iores_fini(struct bhnd_erom_io *eio)
{
	struct bhnd_erom_iores *iores = (struct bhnd_erom_iores *)eio;

	/* Release any mapping */
	if (iores->mapped) {
		bhnd_release_resource(iores->owner, SYS_RES_MEMORY,
		    iores->mapped_rid, iores->mapped);
		iores->mapped = NULL;
		iores->mapped_rid = -1;
	}

	free(eio, M_BHND);
}
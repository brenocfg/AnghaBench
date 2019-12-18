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
struct bhnd_nvram_bcm_hvar {int /*<<< orphan*/  name; } ;
struct bhnd_nvram_bcm {struct bhnd_nvram_bcm_hvar* hvars; } ;

/* Variables and functions */
 size_t nitems (struct bhnd_nvram_bcm_hvar*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct bhnd_nvram_bcm_hvar *
bhnd_nvram_bcm_gethdrvar(struct bhnd_nvram_bcm *bcm, const char *name)
{
	for (size_t i = 0; i < nitems(bcm->hvars); i++) {
		if (strcmp(bcm->hvars[i].name, name) == 0)
			return (&bcm->hvars[i]);
	}

	/* Not found */
	return (NULL);
}
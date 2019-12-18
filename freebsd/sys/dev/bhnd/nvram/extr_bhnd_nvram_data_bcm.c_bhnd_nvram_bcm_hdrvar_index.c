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
struct bhnd_nvram_bcm_hvar {int dummy; } ;
struct bhnd_nvram_bcm {struct bhnd_nvram_bcm_hvar* hvars; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_ASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * bhnd_nvram_bcm_to_hdrvar (struct bhnd_nvram_bcm*,void*) ; 

__attribute__((used)) static size_t
bhnd_nvram_bcm_hdrvar_index(struct bhnd_nvram_bcm *bcm,
    struct bhnd_nvram_bcm_hvar *hdrvar)
{
	BHND_NV_ASSERT(bhnd_nvram_bcm_to_hdrvar(bcm, (void *)hdrvar) != NULL,
	    ("%p is not a valid hdrvar reference", hdrvar));

	return (hdrvar - &bcm->hvars[0]);
}
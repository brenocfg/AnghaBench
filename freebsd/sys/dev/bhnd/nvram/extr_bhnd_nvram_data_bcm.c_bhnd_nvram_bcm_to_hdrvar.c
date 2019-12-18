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
struct bhnd_nvram_bcm {int /*<<< orphan*/ * hvars; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int nitems (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bhnd_nvram_bcm_hvar *
bhnd_nvram_bcm_to_hdrvar(struct bhnd_nvram_bcm *bcm, void *cookiep)
{
#ifdef BHND_NVRAM_INVARIANTS                                                                                                                                                                                                                                
	uintptr_t base, ptr;
#endif

	/* If the cookie falls within the hvar array, it's a
	 * header variable cookie */
	if (nitems(bcm->hvars) == 0)
		return (NULL);

	if (cookiep < (void *)&bcm->hvars[0])
		return (NULL);

	if (cookiep > (void *)&bcm->hvars[nitems(bcm->hvars)-1])
		return (NULL);

#ifdef BHND_NVRAM_INVARIANTS
	base = (uintptr_t)bcm->hvars;
	ptr = (uintptr_t)cookiep;

	BHND_NV_ASSERT((ptr - base) % sizeof(bcm->hvars[0]) == 0,
	    ("misaligned hvar pointer %p/%p", cookiep, bcm->hvars));
#endif /* INVARIANTS */

	return ((struct bhnd_nvram_bcm_hvar *)cookiep);
}
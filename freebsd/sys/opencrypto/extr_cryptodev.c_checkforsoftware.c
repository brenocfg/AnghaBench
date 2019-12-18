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

/* Variables and functions */
 int CRYPTOCAP_F_HARDWARE ; 
 int CRYPTOCAP_F_SOFTWARE ; 
 int EINVAL ; 
 int /*<<< orphan*/  crypto_devallowsoft ; 
 int crypto_getcaps (int) ; 

__attribute__((used)) static int
checkforsoftware(int *cridp)
{
	int crid;

	crid = *cridp;

	if (!crypto_devallowsoft) {
		if (crid & CRYPTOCAP_F_SOFTWARE) {
			if (crid & CRYPTOCAP_F_HARDWARE) {
				*cridp = CRYPTOCAP_F_HARDWARE;
				return 0;
			}
			return EINVAL;
		}
		if ((crid & CRYPTOCAP_F_HARDWARE) == 0 &&
		    (crypto_getcaps(crid) & CRYPTOCAP_F_HARDWARE) == 0)
			return EINVAL;
	}
	return 0;
}
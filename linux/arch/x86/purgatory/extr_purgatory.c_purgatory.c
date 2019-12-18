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
 int /*<<< orphan*/  copy_backup_region () ; 
 int verify_sha256_digest () ; 

void purgatory(void)
{
	int ret;

	ret = verify_sha256_digest();
	if (ret) {
		/* loop forever */
		for (;;)
			;
	}
	copy_backup_region();
}
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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 scalar_t__ ARCHIVE_OK ; 
 int TRAD_HEADER_SIZE ; 
 scalar_t__ archive_random (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
is_traditional_pkware_encryption_supported(void)
{
	uint8_t key[TRAD_HEADER_SIZE];

	if (archive_random(key, sizeof(key)-1) != ARCHIVE_OK)
		return (0);
	return (1);
}
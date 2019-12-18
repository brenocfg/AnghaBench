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
 size_t ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  floppy_type ; 

__attribute__((used)) static bool valid_floppy_drive_params(const short autodetect[8],
		int native_format)
{
	size_t floppy_type_size = ARRAY_SIZE(floppy_type);
	size_t i = 0;

	for (i = 0; i < 8; ++i) {
		if (autodetect[i] < 0 ||
		    autodetect[i] >= floppy_type_size)
			return false;
	}

	if (native_format < 0 || native_format >= floppy_type_size)
		return false;

	return true;
}
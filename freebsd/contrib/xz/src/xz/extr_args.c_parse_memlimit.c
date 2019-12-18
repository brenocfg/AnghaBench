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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int UINT64_MAX ; 
 int /*<<< orphan*/  hardware_memlimit_set (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  str_to_uint64 (char const*,char*,int,int) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void
parse_memlimit(const char *name, const char *name_percentage, char *str,
		bool set_compress, bool set_decompress)
{
	bool is_percentage = false;
	uint64_t value;

	const size_t len = strlen(str);
	if (len > 0 && str[len - 1] == '%') {
		str[len - 1] = '\0';
		is_percentage = true;
		value = str_to_uint64(name_percentage, str, 1, 100);
	} else {
		// On 32-bit systems, SIZE_MAX would make more sense than
		// UINT64_MAX. But use UINT64_MAX still so that scripts
		// that assume > 4 GiB values don't break.
		value = str_to_uint64(name, str, 0, UINT64_MAX);
	}

	hardware_memlimit_set(
			value, set_compress, set_decompress, is_percentage);
	return;
}
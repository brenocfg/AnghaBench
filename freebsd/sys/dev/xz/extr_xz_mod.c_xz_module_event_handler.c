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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  xz_crc32_init () ; 
 int /*<<< orphan*/  xz_crc64_init () ; 

__attribute__((used)) static int
xz_module_event_handler(module_t mod, int what, void *arg)
{
	int error;

	switch (what) {
	case MOD_LOAD:
#if XZ_INTERNAL_CRC32
		xz_crc32_init();
#endif
#if XZ_INTERNAL_CRC64
		xz_crc64_init();
#endif
		error = 0;
		break;
	case MOD_UNLOAD:
		error = 0;
		break;
	default:
		error = EOPNOTSUPP;
		break;
	}

	return (error);
}
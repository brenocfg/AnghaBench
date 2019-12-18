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
typedef  void* uint8_t ;
typedef  void* uint64_t ;
typedef  void* uint32_t ;
typedef  void* uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

__attribute__((used)) static void
stv(int len, void *addr, uint64_t value)
{
	switch (len) {
	case 1:
		*(uint8_t *)addr = value;
		return;
	case 2:
		*(uint16_t *)addr = value;
		return;
	case 4:
		*(uint32_t *)addr = value;
		return;
	case 8:
		*(uint64_t *)addr = value;
		return;
	}
	ASSERT(!"bad int len");
}
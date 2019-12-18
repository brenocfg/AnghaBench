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

/* Variables and functions */
 int AMDVI_EVENT_FLAG_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static inline void
amdvi_decode_evt_flag_type(uint8_t type)
{

	switch (AMDVI_EVENT_FLAG_TYPE(type)) {
	case 0:
		printf("RSVD\n");
		break;
	case 1:
		printf("Master Abort\n");
		break;
	case 2:
		printf("Target Abort\n");
		break;
	case 3:
		printf("Data Err\n");
		break;
	default:
		break;
	}
}
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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMDVI_EVENT_FLAG_MASK ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline void
amdvi_decode_evt_flag(uint16_t flag)
{

	flag &= AMDVI_EVENT_FLAG_MASK;
	printf(" 0x%b]\n", flag,
		"\020"
		"\001GN"
		"\002NX"
		"\003US"
		"\004I"
		"\005PR"
		"\006RW"
		"\007PE"
		"\010RZ"
		"\011TR"
		);
}
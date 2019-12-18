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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/ * ADDR1 ; 
 int /*<<< orphan*/ * ADDR2 ; 
 int /*<<< orphan*/ * ADDR3 ; 
 int /*<<< orphan*/ * ADDR4 ; 
 int /*<<< orphan*/  FC_FROM_DS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_TO_DS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_data_src_dst_mac(uint16_t fc, const u_char *p, const uint8_t **srcp,
                     const uint8_t **dstp)
{
#define ADDR1  (p + 4)
#define ADDR2  (p + 10)
#define ADDR3  (p + 16)
#define ADDR4  (p + 24)

	if (!FC_TO_DS(fc)) {
		if (!FC_FROM_DS(fc)) {
			/* not To DS and not From DS */
			*srcp = ADDR2;
			*dstp = ADDR1;
		} else {
			/* not To DS and From DS */
			*srcp = ADDR3;
			*dstp = ADDR1;
		}
	} else {
		if (!FC_FROM_DS(fc)) {
			/* From DS and not To DS */
			*srcp = ADDR2;
			*dstp = ADDR3;
		} else {
			/* To DS and From DS */
			*srcp = ADDR4;
			*dstp = ADDR3;
		}
	}

#undef ADDR1
#undef ADDR2
#undef ADDR3
#undef ADDR4
}
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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ B_KEYIN ; 
 scalar_t__ F_TLV_KEYI ; 
 scalar_t__ F_TLV_PDAT ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
chk_op_type(netdissect_options *ndo,
            uint16_t type, uint16_t msk, uint16_t omsk)
{
	if (type != F_TLV_PDAT) {
		if (msk & B_KEYIN) {
			if (type != F_TLV_KEYI) {
				ND_PRINT((ndo, "Based on flags expected KEYINFO TLV!\n"));
			}
		} else {
			if (!(msk & omsk)) {
				ND_PRINT((ndo, "Illegal DATA encoding for type 0x%x programmed %x got %x \n",
				          type, omsk, msk));
			}
		}
	}

}
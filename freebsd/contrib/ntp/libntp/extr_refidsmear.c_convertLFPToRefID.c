#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int l_ui; int l_uf; } ;
typedef  TYPE_1__ l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  L_ADDUF (TYPE_1__*,int) ; 
 int UINT32_C (int) ; 
 int htonl (int) ; 

uint32_t
convertLFPToRefID(l_fp num)
{
	uint32_t temp;

	/* round the input with the highest bit to shift out from the
	 * fraction, then keep just two bits from the integral part.
	 *
	 * TODO: check for overflows; should we clamp/saturate or just
	 * complain?
	 */
	L_ADDUF(&num, 0x200);
	num.l_ui &= 3;

	/* combine integral and fractional part to 24 bits */
	temp  = (num.l_ui << 22) | (num.l_uf >> 10);

	/* put in the leading 254.0.0.0 */
	temp |= UINT32_C(0xFE000000);

	// printf("%03d %08x: ", (temp >> 24) & 0xFF, (temp & 0x00FFFFFF) );

	return htonl(temp);
}
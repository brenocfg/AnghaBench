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
typedef  int /*<<< orphan*/  xkey ;
typedef  int /*<<< orphan*/  w ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ fips186_2_prf (int*,int,int*,int) ; 
 scalar_t__ os_memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int test_fips186_2_prf(void)
{
	/* http://csrc.nist.gov/encryption/dss/Examples-1024bit.pdf */
	u8 xkey[] = {
		0xbd, 0x02, 0x9b, 0xbe, 0x7f, 0x51, 0x96, 0x0b,
		0xcf, 0x9e, 0xdb, 0x2b, 0x61, 0xf0, 0x6f, 0x0f,
		0xeb, 0x5a, 0x38, 0xb6
	};
	u8 w[] = {
		0x20, 0x70, 0xb3, 0x22, 0x3d, 0xba, 0x37, 0x2f,
		0xde, 0x1c, 0x0f, 0xfc, 0x7b, 0x2e, 0x3b, 0x49,
		0x8b, 0x26, 0x06, 0x14, 0x3c, 0x6c, 0x18, 0xba,
		0xcb, 0x0f, 0x6c, 0x55, 0xba, 0xbb, 0x13, 0x78,
		0x8e, 0x20, 0xd7, 0x37, 0xa3, 0x27, 0x51, 0x16
	};
	u8 buf[40];

	wpa_printf(MSG_INFO,
		   "Testing EAP-SIM PRF (FIPS 186-2 + change notice 1)");
	if (fips186_2_prf(xkey, sizeof(xkey), buf, sizeof(buf)) < 0 ||
	    os_memcmp(w, buf, sizeof(w)) != 0) {
		wpa_printf(MSG_INFO, "fips186_2_prf failed");
		return 1;
	}

	return 0;
}
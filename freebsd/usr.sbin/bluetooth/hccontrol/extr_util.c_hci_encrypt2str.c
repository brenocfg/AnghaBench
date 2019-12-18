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
 int SIZE (char const* const*) ; 

char const *
hci_encrypt2str(int encrypt, int brief)
{
	static char const * const	t[] = {
		/* 0x00 */ "Disabled",
		/* 0x01 */ "Only for point-to-point packets",
		/* 0x02 */ "Both point-to-point and broadcast packets"
	};

	static char const * const	t1[] = {
		/* NG_HCI_ENCRYPTION_MODE_NONE */ "NONE",
		/* NG_HCI_ENCRYPTION_MODE_P2P */  "P2P",
		/* NG_HCI_ENCRYPTION_MODE_ALL */  "ALL",
	};

	if (brief)
		return (encrypt >= SIZE(t1)? "?" : t1[encrypt]);

	return (encrypt >= SIZE(t)? "?" : t[encrypt]);
}
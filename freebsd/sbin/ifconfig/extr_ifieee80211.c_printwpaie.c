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
typedef  int u_int8_t ;

/* Variables and functions */
 int LE_READ_2 (int const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ verbose ; 
 char* wpa_cipher (int const*) ; 
 int /*<<< orphan*/  wpa_keymgmt (int const*) ; 

__attribute__((used)) static void
printwpaie(const char *tag, const u_int8_t *ie, size_t ielen, int maxlen)
{
	u_int8_t len = ie[1];

	printf("%s", tag);
	if (verbose) {
		const char *sep;
		int n;

		ie += 6, len -= 4;		/* NB: len is payload only */

		printf("<v%u", LE_READ_2(ie));
		ie += 2, len -= 2;

		printf(" mc:%s", wpa_cipher(ie));
		ie += 4, len -= 4;

		/* unicast ciphers */
		n = LE_READ_2(ie);
		ie += 2, len -= 2;
		sep = " uc:";
		for (; n > 0; n--) {
			printf("%s%s", sep, wpa_cipher(ie));
			ie += 4, len -= 4;
			sep = "+";
		}

		/* key management algorithms */
		n = LE_READ_2(ie);
		ie += 2, len -= 2;
		sep = " km:";
		for (; n > 0; n--) {
			printf("%s%s", sep, wpa_keymgmt(ie));
			ie += 4, len -= 4;
			sep = "+";
		}

		if (len > 2)		/* optional capabilities */
			printf(", caps 0x%x", LE_READ_2(ie));
		printf(">");
	}
}
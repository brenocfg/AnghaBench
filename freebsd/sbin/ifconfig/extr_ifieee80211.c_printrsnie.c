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
typedef  int /*<<< orphan*/  u_int8_t ;

/* Variables and functions */
 int LE_READ_2 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* rsn_cipher (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  rsn_keymgmt (int /*<<< orphan*/  const*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
printrsnie(const char *tag, const u_int8_t *ie, size_t ielen, int maxlen)
{
	printf("%s", tag);
	if (verbose) {
		const char *sep;
		int n;

		ie += 2, ielen -= 2;

		printf("<v%u", LE_READ_2(ie));
		ie += 2, ielen -= 2;

		printf(" mc:%s", rsn_cipher(ie));
		ie += 4, ielen -= 4;

		/* unicast ciphers */
		n = LE_READ_2(ie);
		ie += 2, ielen -= 2;
		sep = " uc:";
		for (; n > 0; n--) {
			printf("%s%s", sep, rsn_cipher(ie));
			ie += 4, ielen -= 4;
			sep = "+";
		}

		/* key management algorithms */
		n = LE_READ_2(ie);
		ie += 2, ielen -= 2;
		sep = " km:";
		for (; n > 0; n--) {
			printf("%s%s", sep, rsn_keymgmt(ie));
			ie += 4, ielen -= 4;
			sep = "+";
		}

		if (ielen > 2)		/* optional capabilities */
			printf(", caps 0x%x", LE_READ_2(ie));
		/* XXXPMKID */
		printf(">");
	}
}
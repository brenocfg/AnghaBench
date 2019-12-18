#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_3__ {size_t keylen; int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ sctp_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_PRINTF (char*,...) ; 

void
sctp_show_key(sctp_key_t *key, const char *str)
{
	uint32_t i;

	if (key == NULL) {
		SCTP_PRINTF("%s: [Null key]\n", str);
		return;
	}
	SCTP_PRINTF("%s: len %u, ", str, key->keylen);
	if (key->keylen) {
		for (i = 0; i < key->keylen; i++)
			SCTP_PRINTF("%02x", key->key[i]);
		SCTP_PRINTF("\n");
	} else {
		SCTP_PRINTF("[Null key]\n");
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__* key; } ;
typedef  TYPE_1__ sctp_key_t ;

/* Variables and functions */
 scalar_t__ sctp_get_keylen (TYPE_1__*) ; 

__attribute__((used)) static int
sctp_compare_key(sctp_key_t *key1, sctp_key_t *key2)
{
	uint32_t maxlen;
	uint32_t i;
	uint32_t key1len, key2len;
	uint8_t *key_1, *key_2;
	uint8_t val1, val2;

	/* sanity/length check */
	key1len = sctp_get_keylen(key1);
	key2len = sctp_get_keylen(key2);
	if ((key1len == 0) && (key2len == 0))
		return (0);
	else if (key1len == 0)
		return (-1);
	else if (key2len == 0)
		return (1);

	if (key1len < key2len) {
		maxlen = key2len;
	} else {
		maxlen = key1len;
	}
	key_1 = key1->key;
	key_2 = key2->key;
	/* check for numeric equality */
	for (i = 0; i < maxlen; i++) {
		/* left-pad with zeros */
		val1 = (i < (maxlen - key1len)) ? 0 : *(key_1++);
		val2 = (i < (maxlen - key2len)) ? 0 : *(key_2++);
		if (val1 > val2) {
			return (1);
		} else if (val1 < val2) {
			return (-1);
		}
	}
	/* keys are equal value, so check lengths */
	if (key1len == key2len)
		return (0);
	else if (key1len < key2len)
		return (-1);
	else
		return (1);
}
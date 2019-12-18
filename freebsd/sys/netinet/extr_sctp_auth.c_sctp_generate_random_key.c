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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ sctp_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_READ_RANDOM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* sctp_alloc_key (int /*<<< orphan*/ ) ; 

sctp_key_t *
sctp_generate_random_key(uint32_t keylen)
{
	sctp_key_t *new_key;

	new_key = sctp_alloc_key(keylen);
	if (new_key == NULL) {
		/* out of memory */
		return (NULL);
	}
	SCTP_READ_RANDOM(new_key->key, keylen);
	new_key->keylen = keylen;
	return (new_key);
}
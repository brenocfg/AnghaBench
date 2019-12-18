#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  keyid; TYPE_2__* key; } ;
typedef  TYPE_1__ sctp_sharedkey_t ;
struct TYPE_7__ {int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 TYPE_1__* sctp_alloc_sharedkey () ; 
 TYPE_2__* sctp_set_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sctp_sharedkey_t *
sctp_copy_sharedkey(const sctp_sharedkey_t *skey)
{
	sctp_sharedkey_t *new_skey;

	if (skey == NULL)
		return (NULL);
	new_skey = sctp_alloc_sharedkey();
	if (new_skey == NULL)
		return (NULL);
	if (skey->key != NULL)
		new_skey->key = sctp_set_key(skey->key->key, skey->key->keylen);
	else
		new_skey->key = NULL;
	new_skey->keyid = skey->keyid;
	return (new_skey);
}
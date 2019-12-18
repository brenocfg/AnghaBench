#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct pkcs7_signed_info {TYPE_1__* sig; int /*<<< orphan*/ * next; } ;
struct pkcs7_message {struct pkcs7_signed_info* signed_infos; } ;
typedef  enum hash_algo { ____Placeholder_hash_algo } hash_algo ;
struct TYPE_2__ {int /*<<< orphan*/  hash_algo; int /*<<< orphan*/  digest_size; int /*<<< orphan*/ * digest; } ;

/* Variables and functions */
 int EBADMSG ; 
 int HASH_ALGO__LAST ; 
 int /*<<< orphan*/ * hash_algo_name ; 
 int pkcs7_digest (struct pkcs7_message*,struct pkcs7_signed_info*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pkcs7_get_digest(struct pkcs7_message *pkcs7, const u8 **buf, u32 *len,
		     enum hash_algo *hash_algo)
{
	struct pkcs7_signed_info *sinfo = pkcs7->signed_infos;
	int i, ret;

	/*
	 * This function doesn't support messages with more than one signature.
	 */
	if (sinfo == NULL || sinfo->next != NULL)
		return -EBADMSG;

	ret = pkcs7_digest(pkcs7, sinfo);
	if (ret)
		return ret;

	*buf = sinfo->sig->digest;
	*len = sinfo->sig->digest_size;

	for (i = 0; i < HASH_ALGO__LAST; i++)
		if (!strcmp(hash_algo_name[i], sinfo->sig->hash_algo)) {
			*hash_algo = i;
			break;
		}

	return 0;
}
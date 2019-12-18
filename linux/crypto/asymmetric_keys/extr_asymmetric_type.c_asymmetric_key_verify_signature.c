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
struct public_key_signature {void* digest; void* s; int /*<<< orphan*/  hash_algo; int /*<<< orphan*/  encoding; int /*<<< orphan*/  digest_size; int /*<<< orphan*/  s_size; } ;
struct kernel_pkey_params {int /*<<< orphan*/  key; int /*<<< orphan*/  hash_algo; int /*<<< orphan*/  encoding; int /*<<< orphan*/  in_len; int /*<<< orphan*/  in2_len; } ;

/* Variables and functions */
 int verify_signature (int /*<<< orphan*/ ,struct public_key_signature*) ; 

__attribute__((used)) static int asymmetric_key_verify_signature(struct kernel_pkey_params *params,
					   const void *in, const void *in2)
{
	struct public_key_signature sig = {
		.s_size		= params->in2_len,
		.digest_size	= params->in_len,
		.encoding	= params->encoding,
		.hash_algo	= params->hash_algo,
		.digest		= (void *)in,
		.s		= (void *)in2,
	};

	return verify_signature(params->key, &sig);
}
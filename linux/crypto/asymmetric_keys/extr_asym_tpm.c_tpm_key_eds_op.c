#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tpm_key {int dummy; } ;
struct kernel_pkey_params {int op; TYPE_2__* key; } ;
struct TYPE_3__ {struct tpm_key** data; } ;
struct TYPE_4__ {TYPE_1__ payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EOPNOTSUPP ; 
 size_t asym_crypto ; 
#define  kernel_pkey_decrypt 130 
#define  kernel_pkey_encrypt 129 
#define  kernel_pkey_sign 128 
 int tpm_key_decrypt (struct tpm_key*,struct kernel_pkey_params*,void const*,void*) ; 
 int tpm_key_encrypt (struct tpm_key*,struct kernel_pkey_params*,void const*,void*) ; 
 int tpm_key_sign (struct tpm_key*,struct kernel_pkey_params*,void const*,void*) ; 

__attribute__((used)) static int tpm_key_eds_op(struct kernel_pkey_params *params,
			  const void *in, void *out)
{
	struct tpm_key *tk = params->key->payload.data[asym_crypto];
	int ret = -EOPNOTSUPP;

	/* Perform the encryption calculation. */
	switch (params->op) {
	case kernel_pkey_encrypt:
		ret = tpm_key_encrypt(tk, params, in, out);
		break;
	case kernel_pkey_decrypt:
		ret = tpm_key_decrypt(tk, params, in, out);
		break;
	case kernel_pkey_sign:
		ret = tpm_key_sign(tk, params, in, out);
		break;
	default:
		BUG();
	}

	return ret;
}
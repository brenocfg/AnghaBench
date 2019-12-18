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
struct tpm_key {int /*<<< orphan*/  owner; } ;
struct TYPE_2__ {struct tpm_key** data; } ;
struct key_preparsed_payload {int datalen; int quotalen; TYPE_1__ payload; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 scalar_t__ IS_ERR (struct tpm_key*) ; 
 int PTR_ERR (struct tpm_key*) ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 size_t asym_auth ; 
 size_t asym_crypto ; 
 size_t asym_key_ids ; 
 size_t asym_subtype ; 
 struct tpm_key asym_tpm_subtype ; 
 struct tpm_key* tpm_parse (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tpm_key_preparse(struct key_preparsed_payload *prep)
{
	struct tpm_key *tk;

	/*
	 * TPM 1.2 keys are max 2048 bits long, so assume the blob is no
	 * more than 4x that
	 */
	if (prep->datalen > 256 * 4)
		return -EMSGSIZE;

	tk = tpm_parse(prep->data, prep->datalen);

	if (IS_ERR(tk))
		return PTR_ERR(tk);

	/* We're pinning the module by being linked against it */
	__module_get(asym_tpm_subtype.owner);
	prep->payload.data[asym_subtype] = &asym_tpm_subtype;
	prep->payload.data[asym_key_ids] = NULL;
	prep->payload.data[asym_crypto] = tk;
	prep->payload.data[asym_auth] = NULL;
	prep->quotalen = 100;
	return 0;
}
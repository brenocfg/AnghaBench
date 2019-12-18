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
struct public_key {char* id_type; int /*<<< orphan*/  owner; int /*<<< orphan*/  pkey_algo; } ;
struct TYPE_2__ {struct public_key** data; } ;
struct key_preparsed_payload {int quotalen; TYPE_1__ payload; int /*<<< orphan*/  datalen; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct public_key*) ; 
 int PTR_ERR (struct public_key*) ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 size_t asym_auth ; 
 size_t asym_crypto ; 
 size_t asym_key_ids ; 
 size_t asym_subtype ; 
 struct public_key* pkcs8_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ) ; 
 struct public_key public_key_subtype ; 

__attribute__((used)) static int pkcs8_key_preparse(struct key_preparsed_payload *prep)
{
	struct public_key *pub;

	pub = pkcs8_parse(prep->data, prep->datalen);
	if (IS_ERR(pub))
		return PTR_ERR(pub);

	pr_devel("Cert Key Algo: %s\n", pub->pkey_algo);
	pub->id_type = "PKCS8";

	/* We're pinning the module by being linked against it */
	__module_get(public_key_subtype.owner);
	prep->payload.data[asym_subtype] = &public_key_subtype;
	prep->payload.data[asym_key_ids] = NULL;
	prep->payload.data[asym_crypto] = pub;
	prep->payload.data[asym_auth] = NULL;
	prep->quotalen = 100;
	return 0;
}
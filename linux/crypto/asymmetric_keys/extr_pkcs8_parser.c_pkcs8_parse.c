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
struct public_key {int key_is_private; int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; } ;
struct pkcs8_parse_context {unsigned long data; struct public_key* pub; int /*<<< orphan*/  key_size; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  ctx ;

/* Variables and functions */
 long ENOMEM ; 
 struct public_key* ERR_PTR (long) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 long asn1_ber_decoder (int /*<<< orphan*/ *,struct pkcs8_parse_context*,void const*,size_t) ; 
 int /*<<< orphan*/  kfree (struct public_key*) ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct public_key* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pkcs8_parse_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pkcs8_decoder ; 

__attribute__((used)) static struct public_key *pkcs8_parse(const void *data, size_t datalen)
{
	struct pkcs8_parse_context ctx;
	struct public_key *pub;
	long ret;

	memset(&ctx, 0, sizeof(ctx));

	ret = -ENOMEM;
	ctx.pub = kzalloc(sizeof(struct public_key), GFP_KERNEL);
	if (!ctx.pub)
		goto error;

	ctx.data = (unsigned long)data;

	/* Attempt to decode the private key */
	ret = asn1_ber_decoder(&pkcs8_decoder, &ctx, data, datalen);
	if (ret < 0)
		goto error_decode;

	ret = -ENOMEM;
	pub = ctx.pub;
	pub->key = kmemdup(ctx.key, ctx.key_size, GFP_KERNEL);
	if (!pub->key)
		goto error_decode;

	pub->keylen = ctx.key_size;
	pub->key_is_private = true;
	return pub;

error_decode:
	kfree(ctx.pub);
error:
	return ERR_PTR(ret);
}
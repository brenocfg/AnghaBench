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
struct x509_parse_context {unsigned long data; void const* raw_akid; size_t raw_akid_size; int /*<<< orphan*/  key_algo; int /*<<< orphan*/  params_size; int /*<<< orphan*/  params; int /*<<< orphan*/  key_size; int /*<<< orphan*/  key; struct x509_certificate* cert; } ;
struct x509_certificate {struct asymmetric_key_id* id; int /*<<< orphan*/  raw_issuer_size; int /*<<< orphan*/  raw_issuer; int /*<<< orphan*/  raw_serial_size; int /*<<< orphan*/  raw_serial; TYPE_1__* pub; void* sig; } ;
struct public_key_signature {int dummy; } ;
struct public_key {int dummy; } ;
struct asymmetric_key_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  algo; int /*<<< orphan*/  paramlen; void* params; int /*<<< orphan*/  keylen; void* key; } ;

/* Variables and functions */
 long ENOMEM ; 
 struct x509_certificate* ERR_PTR (long) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct asymmetric_key_id*) ; 
 long PTR_ERR (struct asymmetric_key_id*) ; 
 long asn1_ber_decoder (int /*<<< orphan*/ *,struct x509_parse_context*,void const*,size_t) ; 
 struct asymmetric_key_id* asymmetric_key_generate_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct x509_parse_context*) ; 
 void* kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*,size_t,size_t,void const*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  x509_akid_decoder ; 
 long x509_check_for_self_signed (struct x509_certificate*) ; 
 int /*<<< orphan*/  x509_decoder ; 
 int /*<<< orphan*/  x509_free_certificate (struct x509_certificate*) ; 
 long x509_get_sig_params (struct x509_certificate*) ; 

struct x509_certificate *x509_cert_parse(const void *data, size_t datalen)
{
	struct x509_certificate *cert;
	struct x509_parse_context *ctx;
	struct asymmetric_key_id *kid;
	long ret;

	ret = -ENOMEM;
	cert = kzalloc(sizeof(struct x509_certificate), GFP_KERNEL);
	if (!cert)
		goto error_no_cert;
	cert->pub = kzalloc(sizeof(struct public_key), GFP_KERNEL);
	if (!cert->pub)
		goto error_no_ctx;
	cert->sig = kzalloc(sizeof(struct public_key_signature), GFP_KERNEL);
	if (!cert->sig)
		goto error_no_ctx;
	ctx = kzalloc(sizeof(struct x509_parse_context), GFP_KERNEL);
	if (!ctx)
		goto error_no_ctx;

	ctx->cert = cert;
	ctx->data = (unsigned long)data;

	/* Attempt to decode the certificate */
	ret = asn1_ber_decoder(&x509_decoder, ctx, data, datalen);
	if (ret < 0)
		goto error_decode;

	/* Decode the AuthorityKeyIdentifier */
	if (ctx->raw_akid) {
		pr_devel("AKID: %u %*phN\n",
			 ctx->raw_akid_size, ctx->raw_akid_size, ctx->raw_akid);
		ret = asn1_ber_decoder(&x509_akid_decoder, ctx,
				       ctx->raw_akid, ctx->raw_akid_size);
		if (ret < 0) {
			pr_warn("Couldn't decode AuthKeyIdentifier\n");
			goto error_decode;
		}
	}

	ret = -ENOMEM;
	cert->pub->key = kmemdup(ctx->key, ctx->key_size, GFP_KERNEL);
	if (!cert->pub->key)
		goto error_decode;

	cert->pub->keylen = ctx->key_size;

	cert->pub->params = kmemdup(ctx->params, ctx->params_size, GFP_KERNEL);
	if (!cert->pub->params)
		goto error_decode;

	cert->pub->paramlen = ctx->params_size;
	cert->pub->algo = ctx->key_algo;

	/* Grab the signature bits */
	ret = x509_get_sig_params(cert);
	if (ret < 0)
		goto error_decode;

	/* Generate cert issuer + serial number key ID */
	kid = asymmetric_key_generate_id(cert->raw_serial,
					 cert->raw_serial_size,
					 cert->raw_issuer,
					 cert->raw_issuer_size);
	if (IS_ERR(kid)) {
		ret = PTR_ERR(kid);
		goto error_decode;
	}
	cert->id = kid;

	/* Detect self-signed certificates */
	ret = x509_check_for_self_signed(cert);
	if (ret < 0)
		goto error_decode;

	kfree(ctx);
	return cert;

error_decode:
	kfree(ctx);
error_no_ctx:
	x509_free_certificate(cert);
error_no_cert:
	return ERR_PTR(ret);
}
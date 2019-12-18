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
struct x509_parse_context {int last_oid; int algo_oid; TYPE_2__* cert; } ;
struct TYPE_4__ {TYPE_1__* sig; } ;
struct TYPE_3__ {char* hash_algo; char* pkey_algo; char* encoding; } ;

/* Variables and functions */
 int ENOPKG ; 
#define  OID_gost2012Signature256 137 
#define  OID_gost2012Signature512 136 
#define  OID_md2WithRSAEncryption 135 
#define  OID_md3WithRSAEncryption 134 
#define  OID_md4WithRSAEncryption 133 
#define  OID_sha1WithRSAEncryption 132 
#define  OID_sha224WithRSAEncryption 131 
#define  OID_sha256WithRSAEncryption 130 
#define  OID_sha384WithRSAEncryption 129 
#define  OID_sha512WithRSAEncryption 128 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

int x509_note_pkey_algo(void *context, size_t hdrlen,
			unsigned char tag,
			const void *value, size_t vlen)
{
	struct x509_parse_context *ctx = context;

	pr_debug("PubKey Algo: %u\n", ctx->last_oid);

	switch (ctx->last_oid) {
	case OID_md2WithRSAEncryption:
	case OID_md3WithRSAEncryption:
	default:
		return -ENOPKG; /* Unsupported combination */

	case OID_md4WithRSAEncryption:
		ctx->cert->sig->hash_algo = "md4";
		goto rsa_pkcs1;

	case OID_sha1WithRSAEncryption:
		ctx->cert->sig->hash_algo = "sha1";
		goto rsa_pkcs1;

	case OID_sha256WithRSAEncryption:
		ctx->cert->sig->hash_algo = "sha256";
		goto rsa_pkcs1;

	case OID_sha384WithRSAEncryption:
		ctx->cert->sig->hash_algo = "sha384";
		goto rsa_pkcs1;

	case OID_sha512WithRSAEncryption:
		ctx->cert->sig->hash_algo = "sha512";
		goto rsa_pkcs1;

	case OID_sha224WithRSAEncryption:
		ctx->cert->sig->hash_algo = "sha224";
		goto rsa_pkcs1;

	case OID_gost2012Signature256:
		ctx->cert->sig->hash_algo = "streebog256";
		goto ecrdsa;

	case OID_gost2012Signature512:
		ctx->cert->sig->hash_algo = "streebog512";
		goto ecrdsa;
	}

rsa_pkcs1:
	ctx->cert->sig->pkey_algo = "rsa";
	ctx->cert->sig->encoding = "pkcs1";
	ctx->algo_oid = ctx->last_oid;
	return 0;
ecrdsa:
	ctx->cert->sig->pkey_algo = "ecrdsa";
	ctx->cert->sig->encoding = "raw";
	ctx->algo_oid = ctx->last_oid;
	return 0;
}
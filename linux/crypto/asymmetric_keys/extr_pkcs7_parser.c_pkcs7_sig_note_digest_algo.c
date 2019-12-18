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
struct pkcs7_parse_context {int last_oid; TYPE_2__* sinfo; } ;
struct TYPE_4__ {TYPE_1__* sig; } ;
struct TYPE_3__ {char* hash_algo; } ;

/* Variables and functions */
 int ENOPKG ; 
#define  OID_md4 134 
#define  OID_md5 133 
#define  OID_sha1 132 
#define  OID_sha224 131 
#define  OID_sha256 130 
#define  OID_sha384 129 
#define  OID_sha512 128 
 int /*<<< orphan*/  printk (char*,int) ; 

int pkcs7_sig_note_digest_algo(void *context, size_t hdrlen,
			       unsigned char tag,
			       const void *value, size_t vlen)
{
	struct pkcs7_parse_context *ctx = context;

	switch (ctx->last_oid) {
	case OID_md4:
		ctx->sinfo->sig->hash_algo = "md4";
		break;
	case OID_md5:
		ctx->sinfo->sig->hash_algo = "md5";
		break;
	case OID_sha1:
		ctx->sinfo->sig->hash_algo = "sha1";
		break;
	case OID_sha256:
		ctx->sinfo->sig->hash_algo = "sha256";
		break;
	case OID_sha384:
		ctx->sinfo->sig->hash_algo = "sha384";
		break;
	case OID_sha512:
		ctx->sinfo->sig->hash_algo = "sha512";
		break;
	case OID_sha224:
		ctx->sinfo->sig->hash_algo = "sha224";
		break;
	default:
		printk("Unsupported digest algo: %u\n", ctx->last_oid);
		return -ENOPKG;
	}
	return 0;
}
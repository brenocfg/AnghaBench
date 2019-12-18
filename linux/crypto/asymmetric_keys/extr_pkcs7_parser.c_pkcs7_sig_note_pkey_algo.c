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
struct TYPE_3__ {char* pkey_algo; char* encoding; } ;

/* Variables and functions */
 int ENOPKG ; 
#define  OID_rsaEncryption 128 
 int /*<<< orphan*/  printk (char*,int) ; 

int pkcs7_sig_note_pkey_algo(void *context, size_t hdrlen,
			     unsigned char tag,
			     const void *value, size_t vlen)
{
	struct pkcs7_parse_context *ctx = context;

	switch (ctx->last_oid) {
	case OID_rsaEncryption:
		ctx->sinfo->sig->pkey_algo = "rsa";
		ctx->sinfo->sig->encoding = "pkcs1";
		break;
	default:
		printk("Unsupported pkey algo: %u\n", ctx->last_oid);
		return -ENOPKG;
	}
	return 0;
}
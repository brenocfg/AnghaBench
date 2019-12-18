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
struct pkcs8_parse_context {scalar_t__ last_oid; TYPE_1__* pub; } ;
struct TYPE_2__ {char* pkey_algo; } ;

/* Variables and functions */
 int ENOPKG ; 
 scalar_t__ OID_rsaEncryption ; 

int pkcs8_note_algo(void *context, size_t hdrlen,
		    unsigned char tag,
		    const void *value, size_t vlen)
{
	struct pkcs8_parse_context *ctx = context;

	if (ctx->last_oid != OID_rsaEncryption)
		return -ENOPKG;

	ctx->pub->pkey_algo = "rsa";
	return 0;
}
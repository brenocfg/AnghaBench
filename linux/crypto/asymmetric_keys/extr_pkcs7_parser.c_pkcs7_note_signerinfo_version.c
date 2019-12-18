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
typedef  unsigned int u8 ;
struct pkcs7_parse_context {int expect_skid; TYPE_1__* msg; } ;
struct TYPE_2__ {int version; } ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

int pkcs7_note_signerinfo_version(void *context, size_t hdrlen,
				  unsigned char tag,
				  const void *value, size_t vlen)
{
	struct pkcs7_parse_context *ctx = context;
	unsigned version;

	if (vlen != 1)
		goto unsupported;

	version = *(const u8 *)value;
	switch (version) {
	case 1:
		/* PKCS#7 SignerInfo [RFC2315 sec 9.2]
		 * CMS ver 1 SignerInfo [RFC5652 sec 5.3]
		 */
		if (ctx->msg->version != 1)
			goto version_mismatch;
		ctx->expect_skid = false;
		break;
	case 3:
		/* CMS ver 3 SignerInfo [RFC2315 sec 5.3] */
		if (ctx->msg->version == 1)
			goto version_mismatch;
		ctx->expect_skid = true;
		break;
	default:
		goto unsupported;
	}

	return 0;

unsupported:
	pr_warn("Unsupported SignerInfo version\n");
	return -EINVAL;
version_mismatch:
	pr_warn("SignedData-SignerInfo version mismatch\n");
	return -EBADMSG;
}
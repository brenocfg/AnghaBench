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
struct pkcs7_parse_context {TYPE_1__* msg; } ;
struct TYPE_2__ {unsigned int version; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

int pkcs7_note_signeddata_version(void *context, size_t hdrlen,
				  unsigned char tag,
				  const void *value, size_t vlen)
{
	struct pkcs7_parse_context *ctx = context;
	unsigned version;

	if (vlen != 1)
		goto unsupported;

	ctx->msg->version = version = *(const u8 *)value;
	switch (version) {
	case 1:
		/* PKCS#7 SignedData [RFC2315 sec 9.1]
		 * CMS ver 1 SignedData [RFC5652 sec 5.1]
		 */
		break;
	case 3:
		/* CMS ver 3 SignedData [RFC2315 sec 5.1] */
		break;
	default:
		goto unsupported;
	}

	return 0;

unsupported:
	pr_warn("Unsupported SignedData version\n");
	return -EINVAL;
}
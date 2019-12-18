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
struct pkcs7_signed_info {size_t authattrs_len; void const* authattrs; int /*<<< orphan*/  aa_set; } ;
struct pkcs7_parse_context {TYPE_1__* msg; struct pkcs7_signed_info* sinfo; } ;
struct TYPE_2__ {scalar_t__ data_type; } ;

/* Variables and functions */
 int EBADMSG ; 
 scalar_t__ OID_msIndirectData ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  sinfo_has_content_type ; 
 int /*<<< orphan*/  sinfo_has_message_digest ; 
 int /*<<< orphan*/  sinfo_has_ms_opus_info ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int pkcs7_sig_note_set_of_authattrs(void *context, size_t hdrlen,
				    unsigned char tag,
				    const void *value, size_t vlen)
{
	struct pkcs7_parse_context *ctx = context;
	struct pkcs7_signed_info *sinfo = ctx->sinfo;

	if (!test_bit(sinfo_has_content_type, &sinfo->aa_set) ||
	    !test_bit(sinfo_has_message_digest, &sinfo->aa_set)) {
		pr_warn("Missing required AuthAttr\n");
		return -EBADMSG;
	}

	if (ctx->msg->data_type != OID_msIndirectData &&
	    test_bit(sinfo_has_ms_opus_info, &sinfo->aa_set)) {
		pr_warn("Unexpected Authenticode AuthAttr\n");
		return -EBADMSG;
	}

	/* We need to switch the 'CONT 0' to a 'SET OF' when we digest */
	sinfo->authattrs = value - (hdrlen - 1);
	sinfo->authattrs_len = vlen + (hdrlen - 1);
	return 0;
}
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
struct x509_parse_context {TYPE_2__* cert; } ;
struct asymmetric_key_id {int len; void const* data; } ;
struct TYPE_4__ {TYPE_1__* sig; } ;
struct TYPE_3__ {struct asymmetric_key_id** auth_ids; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct asymmetric_key_id*) ; 
 int PTR_ERR (struct asymmetric_key_id*) ; 
 struct asymmetric_key_id* asymmetric_key_generate_id (void const*,size_t,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,void const*) ; 

int x509_akid_note_kid(void *context, size_t hdrlen,
		       unsigned char tag,
		       const void *value, size_t vlen)
{
	struct x509_parse_context *ctx = context;
	struct asymmetric_key_id *kid;

	pr_debug("AKID: keyid: %*phN\n", (int)vlen, value);

	if (ctx->cert->sig->auth_ids[1])
		return 0;

	kid = asymmetric_key_generate_id(value, vlen, "", 0);
	if (IS_ERR(kid))
		return PTR_ERR(kid);
	pr_debug("authkeyid %*phN\n", kid->len, kid->data);
	ctx->cert->sig->auth_ids[1] = kid;
	return 0;
}
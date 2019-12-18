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
struct ecrdsa_ctx {int digest_oid; } ;

/* Variables and functions */
 int EINVAL ; 
 int look_up_OID (void const*,size_t) ; 

int ecrdsa_param_digest(void *context, size_t hdrlen, unsigned char tag,
			const void *value, size_t vlen)
{
	struct ecrdsa_ctx *ctx = context;
	int digest_oid = look_up_OID(value, vlen);

	if (digest_oid != ctx->digest_oid)
		return -EINVAL;
	return 0;
}
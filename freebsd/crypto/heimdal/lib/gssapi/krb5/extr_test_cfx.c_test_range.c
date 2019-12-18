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
typedef  int /*<<< orphan*/  uint16_t ;
struct range {size_t lower; size_t upper; } ;
struct gsskrb5_ctx {int /*<<< orphan*/  crypto; } ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  _gssapi_wrap_size_cfx (scalar_t__*,struct gsskrb5_ctx*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  _gsskrb5cfx_wrap_length_cfx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,size_t*,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,int,...) ; 

__attribute__((used)) static void
test_range(const struct range *r, int integ,
	   krb5_context context, krb5_crypto crypto)
{
    krb5_error_code ret;
    size_t size, rsize;
    struct gsskrb5_ctx ctx;

    for (size = r->lower; size < r->upper; size++) {
	size_t cksumsize;
	uint16_t padsize;
	OM_uint32 minor;
	OM_uint32 max_wrap_size;

	ctx.crypto = crypto;

	ret = _gssapi_wrap_size_cfx(&minor,
				    &ctx,
				    context,
				    integ,
				    0,
				    size,
				    &max_wrap_size);
	if (ret)
	    krb5_errx(context, 1, "_gsskrb5cfx_max_wrap_length_cfx: %d", ret);
	if (max_wrap_size == 0)
	    continue;

	ret = _gsskrb5cfx_wrap_length_cfx(context,
					  crypto,
					  integ,
					  0,
					  max_wrap_size,
					  &rsize, &cksumsize, &padsize);
	if (ret)
	    krb5_errx(context, 1, "_gsskrb5cfx_wrap_length_cfx: %d", ret);

	if (size < rsize)
	    krb5_errx(context, 1,
		      "size (%d) < rsize (%d) for max_wrap_size %d",
		      (int)size, (int)rsize, (int)max_wrap_size);
    }
}
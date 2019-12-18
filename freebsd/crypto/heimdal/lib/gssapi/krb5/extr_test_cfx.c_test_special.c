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
struct gsskrb5_ctx {int /*<<< orphan*/  crypto; } ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ _gssapi_wrap_size_cfx (scalar_t__*,struct gsskrb5_ctx*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t,scalar_t__*) ; 
 scalar_t__ _gsskrb5cfx_wrap_length_cfx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,size_t*,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,int,...) ; 

__attribute__((used)) static void
test_special(krb5_context context, krb5_crypto crypto,
	     int integ, size_t testsize)
{
    krb5_error_code ret;
    size_t rsize;
    OM_uint32 max_wrap_size;
    size_t cksumsize;
    uint16_t padsize;
    struct gsskrb5_ctx ctx;
    OM_uint32 minor;

    ctx.crypto = crypto;

    ret = _gssapi_wrap_size_cfx(&minor,
				&ctx,
				context,
				integ,
				0,
				testsize,
				&max_wrap_size);
    if (ret)
      krb5_errx(context, 1, "_gsskrb5cfx_max_wrap_length_cfx: %d", ret);
    if (ret)
	krb5_errx(context, 1, "_gsskrb5cfx_max_wrap_length_cfx: %d", ret);

    ret = _gsskrb5cfx_wrap_length_cfx(context,
				      crypto,
				      integ,
				      0,
				      max_wrap_size,
				      &rsize, &cksumsize, &padsize);
    if (ret)
	krb5_errx(context, 1, "_gsskrb5cfx_wrap_length_cfx: %d", ret);

    if (testsize < rsize)
	krb5_errx(context, 1,
		  "testsize (%d) < rsize (%d) for max_wrap_size %d",
		  (int)testsize, (int)rsize, (int)max_wrap_size);
}
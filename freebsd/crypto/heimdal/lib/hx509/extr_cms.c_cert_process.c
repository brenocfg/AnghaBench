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
struct TYPE_3__ {TYPE_2__* certificates; } ;
struct sigctx {TYPE_1__ sd; } ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;
struct TYPE_4__ {unsigned int len; int /*<<< orphan*/ * val; } ;

/* Variables and functions */
 int ENOMEM ; 
 int hx509_cert_binary (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* realloc (int /*<<< orphan*/ *,unsigned int const) ; 

__attribute__((used)) static int
cert_process(hx509_context context, void *ctx, hx509_cert cert)
{
    struct sigctx *sigctx = ctx;
    const unsigned int i = sigctx->sd.certificates->len;
    void *ptr;
    int ret;

    ptr = realloc(sigctx->sd.certificates->val,
		  (i + 1) * sizeof(sigctx->sd.certificates->val[0]));
    if (ptr == NULL)
	return ENOMEM;
    sigctx->sd.certificates->val = ptr;

    ret = hx509_cert_binary(context, cert,
			    &sigctx->sd.certificates->val[i]);
    if (ret == 0)
	sigctx->sd.certificates->len++;

    return ret;
}
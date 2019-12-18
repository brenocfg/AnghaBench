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
struct iconv_hooks {int dummy; } ;
struct _citrus_stdenc {TYPE_1__* ce_ops; } ;
typedef  int /*<<< orphan*/  _citrus_wc_t ;
struct TYPE_2__ {int (* eo_wctomb ) (struct _citrus_stdenc*,char*,size_t,int /*<<< orphan*/ ,void*,size_t*,struct iconv_hooks*) ;} ;

/* Variables and functions */
 int stub1 (struct _citrus_stdenc*,char*,size_t,int /*<<< orphan*/ ,void*,size_t*,struct iconv_hooks*) ; 

__attribute__((used)) static __inline int
_citrus_stdenc_wctomb(struct _citrus_stdenc * __restrict ce,
    char * __restrict s, size_t n, _citrus_wc_t wc, void * __restrict ps,
    size_t * __restrict nresult, struct iconv_hooks *hooks)
{

	return ((*ce->ce_ops->eo_wctomb)(ce, s, n, wc, ps, nresult, hooks));
}
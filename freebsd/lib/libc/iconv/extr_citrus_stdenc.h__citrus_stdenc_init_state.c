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
struct _citrus_stdenc {TYPE_1__* ce_ops; } ;
struct TYPE_2__ {int (* eo_init_state ) (struct _citrus_stdenc*,void*) ;} ;

/* Variables and functions */
 int stub1 (struct _citrus_stdenc*,void*) ; 

__attribute__((used)) static __inline int
_citrus_stdenc_init_state(struct _citrus_stdenc * __restrict ce,
    void * __restrict ps)
{

	return ((*ce->ce_ops->eo_init_state)(ce, ps));
}
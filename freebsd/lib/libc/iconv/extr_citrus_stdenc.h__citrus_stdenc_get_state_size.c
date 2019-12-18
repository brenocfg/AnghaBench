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
struct _citrus_stdenc {TYPE_1__* ce_traits; } ;
struct TYPE_2__ {size_t et_state_size; } ;

/* Variables and functions */

__attribute__((used)) static __inline size_t
_citrus_stdenc_get_state_size(struct _citrus_stdenc *ce)
{

	return (ce->ce_traits->et_state_size);
}
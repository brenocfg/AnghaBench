#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {TYPE_1__* extent; } ;
struct TYPE_7__ {TYPE_2__ config; } ;
typedef  TYPE_3__ sli4_t ;
typedef  size_t sli4_resource_e ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 size_t SLI_RSRC_MAX ; 

__attribute__((used)) static inline uint32_t
sli_get_max_rsrc(sli4_t *sli4, sli4_resource_e rsrc)
{
	if (rsrc >= SLI_RSRC_MAX) {
		return 0;
	}

	return sli4->config.extent[rsrc].size;
}
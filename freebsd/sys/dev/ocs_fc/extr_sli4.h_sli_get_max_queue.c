#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * max_qcount; } ;
struct TYPE_5__ {TYPE_1__ config; } ;
typedef  TYPE_2__ sli4_t ;
typedef  size_t sli4_qtype_e ;

/* Variables and functions */
 size_t SLI_QTYPE_MAX ; 

__attribute__((used)) static inline uint32_t
sli_get_max_queue(sli4_t *sli4, sli4_qtype_e qtype)
{
	if (qtype >= SLI_QTYPE_MAX) {
		return 0;
	}
	return sli4->config.max_qcount[qtype];
}
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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  sgl_pre_registered; scalar_t__ sgl_pre_registration_required; } ;
struct TYPE_5__ {TYPE_1__ config; int /*<<< orphan*/  os; } ;
typedef  TYPE_2__ sli4_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline int32_t
sli_set_sgl_preregister(sli4_t *sli4, uint32_t value)
{
	if ((value == 0) && sli4->config.sgl_pre_registration_required) {
		ocs_log_test(sli4->os, "SGL pre-registration required\n");
		return -1;
	}

	sli4->config.sgl_pre_registered = value != 0 ? TRUE : FALSE;

	return 0;
}
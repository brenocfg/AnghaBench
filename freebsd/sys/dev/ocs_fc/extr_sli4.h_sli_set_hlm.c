#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  hlm; } ;
struct TYPE_7__ {TYPE_1__ flag; } ;
struct TYPE_8__ {int /*<<< orphan*/  high_login_mode; TYPE_2__ features; } ;
struct TYPE_9__ {TYPE_3__ config; int /*<<< orphan*/  os; } ;
typedef  TYPE_4__ sli4_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline int32_t
sli_set_hlm(sli4_t *sli4, uint32_t value)
{
	if (value && !sli4->config.features.flag.hlm) {
		ocs_log_test(sli4->os, "HLM not supported\n");
		return -1;
	}

	sli4->config.high_login_mode = value != 0 ? TRUE : FALSE;

	return 0;
}
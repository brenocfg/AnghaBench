#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* rxri; void* rxseq; int /*<<< orphan*/  hlm; } ;
struct TYPE_10__ {TYPE_1__ flag; } ;
struct TYPE_8__ {TYPE_5__ features; int /*<<< orphan*/  high_login_mode; scalar_t__ has_extents; } ;
struct TYPE_9__ {TYPE_2__ config; int /*<<< orphan*/  os; } ;
typedef  TYPE_3__ sli4_t ;
typedef  int int32_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sli_request_features (TYPE_3__*,TYPE_5__*,void*) ; 

int32_t
sli_init(sli4_t *sli4)
{

	if (sli4->config.has_extents) {
		/* TODO COMMON_ALLOC_RESOURCE_EXTENTS */;
		ocs_log_test(sli4->os, "XXX need to implement extent allocation\n");
		return -1;
	}

	sli4->config.features.flag.hlm = sli4->config.high_login_mode;
	sli4->config.features.flag.rxseq = FALSE;
	sli4->config.features.flag.rxri  = FALSE;

	if (sli_request_features(sli4, &sli4->config.features, FALSE)) {
		return -1;
	}

	return 0;
}
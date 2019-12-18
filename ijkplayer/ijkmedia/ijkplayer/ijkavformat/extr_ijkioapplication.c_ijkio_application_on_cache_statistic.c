#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* func_ijkio_on_app_event ) (TYPE_1__*,int /*<<< orphan*/ ,void*,int) ;} ;
typedef  TYPE_1__ IjkIOApplicationContext ;
typedef  int /*<<< orphan*/  IjkIOAppCacheStatistic ;

/* Variables and functions */
 int /*<<< orphan*/  IJKIOAPP_EVENT_CACHE_STATISTIC ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,void*,int) ; 

void ijkio_application_on_cache_statistic(IjkIOApplicationContext *h, IjkIOAppCacheStatistic *statistic) {
    if (h && h->func_ijkio_on_app_event)
        h->func_ijkio_on_app_event(h, IJKIOAPP_EVENT_CACHE_STATISTIC, (void *)statistic, sizeof(IjkIOAppCacheStatistic));
}
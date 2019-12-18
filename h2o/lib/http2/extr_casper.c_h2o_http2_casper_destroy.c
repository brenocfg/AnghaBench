#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* base; } ;
struct TYPE_6__ {TYPE_3__* entries; } ;
struct TYPE_8__ {TYPE_2__ cookie_cache; TYPE_1__ keys; } ;
typedef  TYPE_3__ h2o_http2_casper_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 

void h2o_http2_casper_destroy(h2o_http2_casper_t *casper)
{
    free(casper->keys.entries);
    free(casper->cookie_cache.base);
    free(casper);
}
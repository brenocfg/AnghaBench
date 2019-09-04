#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {scalar_t__ duration; } ;
typedef  TYPE_1__ h2o_cache_t ;
struct TYPE_6__ {scalar_t__ at; } ;
typedef  TYPE_2__ h2o_cache_ref_t ;

/* Variables and functions */

__attribute__((used)) static int64_t get_timeleft(h2o_cache_t *cache, h2o_cache_ref_t *ref, uint64_t now)
{
    return (int64_t)(ref->at + cache->duration) - now;
}
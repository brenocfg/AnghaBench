#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_11__ {scalar_t__ scheme; } ;
typedef  TYPE_2__ h2o_url_t ;
struct TYPE_12__ {TYPE_2__ url; } ;
typedef  TYPE_3__ h2o_socketpool_target_t ;
struct TYPE_10__ {size_t size; TYPE_3__** entries; } ;
struct TYPE_13__ {TYPE_1__ targets; } ;
typedef  TYPE_4__ h2o_socketpool_t ;

/* Variables and functions */
 size_t SIZE_MAX ; 
 scalar_t__ h2o_url_get_port (TYPE_2__*) ; 
 int /*<<< orphan*/  h2o_url_hosts_are_equal (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static size_t lookup_target(h2o_socketpool_t *pool, h2o_url_t *url)
{
    uint16_t port = h2o_url_get_port(url);
    size_t i = 0;
    for (; i != pool->targets.size; ++i) {
        h2o_socketpool_target_t *target = pool->targets.entries[i];
        if (target->url.scheme != url->scheme)
            continue;
        if (h2o_url_get_port(&target->url) != port)
            continue;
        if (!h2o_url_hosts_are_equal(&target->url, url))
            continue;
        return i;
    }
    return SIZE_MAX;
}
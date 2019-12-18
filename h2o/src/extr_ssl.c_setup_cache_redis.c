#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  prefix; } ;
struct TYPE_10__ {TYPE_3__ redis; } ;
struct TYPE_11__ {TYPE_4__ vars; } ;
struct TYPE_7__ {int /*<<< orphan*/  port; int /*<<< orphan*/  host; } ;
struct TYPE_8__ {TYPE_1__ redis; } ;
struct TYPE_12__ {TYPE_5__ cache; int /*<<< orphan*/  lifetime; TYPE_2__ store; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 TYPE_6__ conf ; 
 int /*<<< orphan*/  h2o_accept_setup_redis_ssl_resumption (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_cache_enable (int /*<<< orphan*/ **,size_t,int) ; 

__attribute__((used)) static void setup_cache_redis(SSL_CTX **contexts, size_t num_contexts)
{
    h2o_accept_setup_redis_ssl_resumption(conf.store.redis.host, conf.store.redis.port, conf.lifetime,
                                          conf.cache.vars.redis.prefix);
    setup_cache_enable(contexts, num_contexts, 1);
}
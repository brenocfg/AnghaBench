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
typedef  int /*<<< orphan*/  h2o_socketpool_t ;
struct TYPE_4__ {int /*<<< orphan*/  conns; } ;
struct TYPE_5__ {TYPE_1__ http2; int /*<<< orphan*/ * socketpool; } ;
typedef  TYPE_2__ h2o_httpclient_connection_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_linklist_init_anchor (int /*<<< orphan*/ *) ; 

void h2o_httpclient_connection_pool_init(h2o_httpclient_connection_pool_t *connpool, h2o_socketpool_t *sockpool)
{
    connpool->socketpool = sockpool;
    h2o_linklist_init_anchor(&connpool->http2.conns);
}
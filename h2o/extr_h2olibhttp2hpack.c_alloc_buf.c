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
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
struct TYPE_4__ {char* base; size_t len; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 TYPE_1__* h2o_mem_alloc_shared (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static h2o_iovec_t *alloc_buf(h2o_mem_pool_t *pool, size_t len)
{
    h2o_iovec_t *buf = h2o_mem_alloc_shared(pool, sizeof(h2o_iovec_t) + len + 1, NULL);
    buf->base = (char *)buf + sizeof(h2o_iovec_t);
    buf->len = len;
    return buf;
}
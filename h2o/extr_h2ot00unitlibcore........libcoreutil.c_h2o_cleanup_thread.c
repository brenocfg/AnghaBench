#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  allocator; } ;
struct TYPE_3__ {int /*<<< orphan*/  allocator; } ;

/* Variables and functions */
 TYPE_2__ h2o_http2_wbuf_buffer_prototype ; 
 int /*<<< orphan*/  h2o_mem_clear_recycle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_pool_allocator ; 
 TYPE_1__ h2o_socket_buffer_prototype ; 

void h2o_cleanup_thread(void)
{
    h2o_mem_clear_recycle(&h2o_mem_pool_allocator);
    h2o_mem_clear_recycle(&h2o_http2_wbuf_buffer_prototype.allocator);
    h2o_mem_clear_recycle(&h2o_socket_buffer_prototype.allocator);
}
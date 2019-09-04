#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  bufs; } ;
struct st_h2o_socket_ssl_t {TYPE_1__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_output_buffer(struct st_h2o_socket_ssl_t *ssl)
{
    memset(&ssl->output.bufs, 0, sizeof(ssl->output.bufs));
    h2o_mem_clear_pool(&ssl->output.pool);
}
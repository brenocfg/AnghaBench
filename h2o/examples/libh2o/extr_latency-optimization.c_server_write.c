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
typedef  int /*<<< orphan*/  h2o_socket_t ;
struct TYPE_4__ {char* base; size_t len; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t) ; 
 size_t h2o_socket_prepare_for_latency_optimized_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_socket_write (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  latopt_cond ; 
 TYPE_1__ prepare_write_buf () ; 
 scalar_t__ server_flag_received ; 
 int /*<<< orphan*/  server_on_write_complete ; 
 int /*<<< orphan*/  stderr ; 

void server_write(h2o_socket_t *sock)
{
    size_t sz = h2o_socket_prepare_for_latency_optimized_write(sock, &latopt_cond);
    h2o_iovec_t buf = prepare_write_buf();

    if (server_flag_received)
        buf.base[0] = '1';
    if (sz < buf.len)
        buf.len = sz;

    fprintf(stderr, "writing %zu bytes\n", buf.len);
    h2o_socket_write(sock, &buf, 1, server_on_write_complete);
}
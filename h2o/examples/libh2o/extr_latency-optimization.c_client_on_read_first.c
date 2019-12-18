#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_7__* input; } ;
typedef  TYPE_1__ h2o_socket_t ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ h2o_iovec_t ;
struct TYPE_13__ {int /*<<< orphan*/  bytes_received; int /*<<< orphan*/  bytes_before_sig; int /*<<< orphan*/  resp_start_at; } ;
struct TYPE_12__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  client_on_read_second ; 
 int /*<<< orphan*/  client_on_write_complete ; 
 TYPE_8__ client_stats ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_7__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_get_loop (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_socket_read_start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_write (TYPE_1__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void client_on_read_first(h2o_socket_t *sock, const char *err)
{
    if (err != NULL) {
        fprintf(stderr, "connection closed unexpectedly:%s\n", err);
        exit(1);
        return;
    }

    client_stats.resp_start_at = h2o_now(h2o_socket_get_loop(sock));
    client_stats.bytes_before_sig = sock->input->size;
    client_stats.bytes_received = sock->input->size;
    h2o_buffer_consume(&sock->input, sock->input->size);

    h2o_iovec_t data = {H2O_STRLIT("!")};
    h2o_socket_write(sock, &data, 1, client_on_write_complete);
    h2o_socket_read_start(sock, client_on_read_second);
}
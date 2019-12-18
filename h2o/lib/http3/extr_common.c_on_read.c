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
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ h2o_socket_t ;
typedef  int /*<<< orphan*/  h2o_http3_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_http3_read_socket (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_read(h2o_socket_t *sock, const char *err)
{
    h2o_http3_ctx_t *ctx = sock->data;
    h2o_http3_read_socket(ctx, sock, NULL);
}
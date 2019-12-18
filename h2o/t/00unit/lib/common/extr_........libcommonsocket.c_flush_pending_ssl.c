#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* ssl; } ;
typedef  TYPE_4__ h2o_socket_t ;
typedef  int /*<<< orphan*/  h2o_socket_cb ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  entries; } ;
struct TYPE_8__ {TYPE_1__ bufs; } ;
struct TYPE_9__ {TYPE_2__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_write (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flush_pending_ssl(h2o_socket_t *sock, h2o_socket_cb cb)
{
    do_write(sock, sock->ssl->output.bufs.entries, sock->ssl->output.bufs.size, cb);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void (* cb ) (void*) ;void* data; } ;
struct TYPE_6__ {TYPE_1__ on_close; int /*<<< orphan*/ * _peername; int /*<<< orphan*/  input; int /*<<< orphan*/ * ssl; } ;
typedef  TYPE_2__ h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_ssl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_dispose_socket (TYPE_2__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_buffer_dispose (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dispose_socket(h2o_socket_t *sock, const char *err)
{
    void (*close_cb)(void *data);
    void *close_cb_data;

    if (sock->ssl != NULL) {
        destroy_ssl(sock->ssl);
        sock->ssl = NULL;
    }
    h2o_buffer_dispose(&sock->input);
    if (sock->_peername != NULL) {
        free(sock->_peername);
        sock->_peername = NULL;
    }

    close_cb = sock->on_close.cb;
    close_cb_data = sock->on_close.data;

    do_dispose_socket(sock);

    if (close_cb != NULL)
        close_cb(close_cb_data);
}
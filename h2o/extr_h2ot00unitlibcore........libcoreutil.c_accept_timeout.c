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
struct st_h2o_accept_data_t {int /*<<< orphan*/ * sock; } ;
typedef  int /*<<< orphan*/  h2o_socket_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct st_h2o_accept_data_t*) ;} ;

/* Variables and functions */
 TYPE_1__ accept_data_callbacks ; 
 int /*<<< orphan*/  h2o_socket_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct st_h2o_accept_data_t*) ; 

__attribute__((used)) static void accept_timeout(struct st_h2o_accept_data_t *data)
{
    /* TODO log */
    h2o_socket_t *sock = data->sock;
    accept_data_callbacks.destroy(data);
    h2o_socket_close(sock);
}
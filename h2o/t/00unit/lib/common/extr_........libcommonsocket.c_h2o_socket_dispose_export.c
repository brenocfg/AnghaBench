#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fd; int /*<<< orphan*/  input; int /*<<< orphan*/ * ssl; } ;
typedef  TYPE_1__ h2o_socket_export_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  destroy_ssl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_buffer_dispose (int /*<<< orphan*/ *) ; 

void h2o_socket_dispose_export(h2o_socket_export_t *info)
{
    assert(info->fd != -1);
    if (info->ssl != NULL) {
        destroy_ssl(info->ssl);
        info->ssl = NULL;
    }
    h2o_buffer_dispose(&info->input);
    close(info->fd);
    info->fd = -1;
}
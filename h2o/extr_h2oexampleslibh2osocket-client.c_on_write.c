#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_socket_t ;

/* Variables and functions */
 int exit_loop ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  h2o_socket_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_socket_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_read ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void on_write(h2o_socket_t *sock, const char *err)
{
    if (err != NULL) {
        /* write failed */
        fprintf(stderr, "write failed:%s\n", err);
        h2o_socket_close(sock);
        exit_loop = 1;
        return;
    }

    h2o_socket_read_start(sock, on_read);
}
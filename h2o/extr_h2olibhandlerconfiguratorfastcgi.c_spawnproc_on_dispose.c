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
typedef  int /*<<< orphan*/  h2o_fastcgi_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 

__attribute__((used)) static void spawnproc_on_dispose(h2o_fastcgi_handler_t *handler, void *data)
{
    int pipe_fd = (int)((char *)data - (char *)NULL);
    close(pipe_fd);
}
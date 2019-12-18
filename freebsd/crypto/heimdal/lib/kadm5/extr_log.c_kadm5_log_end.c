#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int log_fd; } ;
struct TYPE_4__ {TYPE_2__ log_context; } ;
typedef  TYPE_1__ kadm5_server_context ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;
typedef  TYPE_2__ kadm5_log_context ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_UN ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  flock (int,int /*<<< orphan*/ ) ; 

kadm5_ret_t
kadm5_log_end (kadm5_server_context *context)
{
    kadm5_log_context *log_context = &context->log_context;
    int fd = log_context->log_fd;

    flock (fd, LOCK_UN);
    close(fd);
    log_context->log_fd = -1;
    return 0;
}
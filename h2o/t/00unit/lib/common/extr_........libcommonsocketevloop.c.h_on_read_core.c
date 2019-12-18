#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_6__ {int len; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ h2o_iovec_t ;
struct TYPE_7__ {int size; } ;
typedef  TYPE_2__ h2o_buffer_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int INT_MAX ; 
 scalar_t__ errno ; 
 TYPE_1__ h2o_buffer_try_reserve (TYPE_2__**,int) ; 
 char const* h2o_socket_error_closed ; 
 char const* h2o_socket_error_io ; 
 char const* h2o_socket_error_out_of_memory ; 
 int read (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static const char *on_read_core(int fd, h2o_buffer_t **input)
{
    int read_any = 0;

    while (1) {
        ssize_t rret;
        h2o_iovec_t buf = h2o_buffer_try_reserve(input, 4096);
        if (buf.base == NULL) {
            /* memory allocation failed */
            return h2o_socket_error_out_of_memory;
        }
        while ((rret = read(fd, buf.base, buf.len <= INT_MAX / 2 ? buf.len : INT_MAX / 2 + 1)) == -1 && errno == EINTR)
            ;
        if (rret == -1) {
            if (errno == EAGAIN)
                break;
            else
                return h2o_socket_error_io;
        } else if (rret == 0) {
            if (!read_any)
                return h2o_socket_error_closed; /* TODO notify close */
            break;
        }
        (*input)->size += rret;
        if (buf.len != rret)
            break;
        read_any = 1;
    }
    return NULL;
}
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
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {TYPE_1__* ref; } ;
struct st_h2o_sendfile_generator_t {TYPE_2__ file; } ;
typedef  int ssize_t ;
struct TYPE_9__ {size_t len; scalar_t__* cb_arg; } ;
typedef  TYPE_3__ h2o_sendvec_t ;
typedef  int /*<<< orphan*/  h2o_req_t ;
struct TYPE_10__ {size_t len; scalar_t__ base; } ;
typedef  TYPE_4__ h2o_iovec_t ;
struct TYPE_7__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int pread (int /*<<< orphan*/ ,scalar_t__,size_t,scalar_t__) ; 

__attribute__((used)) static int do_pread(h2o_sendvec_t *src, h2o_req_t *req, h2o_iovec_t dst, size_t off)
{
    struct st_h2o_sendfile_generator_t *self = (void *)src->cb_arg[0];
    uint64_t file_chunk_at = src->cb_arg[1];
    size_t bytes_read = 0;
    ssize_t rret;

    assert(off + dst.len <= src->len);

    /* read */
    while (bytes_read < dst.len) {
        while ((rret = pread(self->file.ref->fd, dst.base + bytes_read, dst.len - bytes_read, file_chunk_at + off + bytes_read)) ==
                   -1 &&
               errno == EINTR)
            ;
        if (rret == -1)
            return 0;
        bytes_read += rret;
    }

    return 1;
}
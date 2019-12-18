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
struct fd_lookup_st {struct fd_lookup_st* next; int /*<<< orphan*/  fd; scalar_t__ del; } ;
struct TYPE_3__ {struct fd_lookup_st* fds; } ;
typedef  int /*<<< orphan*/  OSSL_ASYNC_FD ;
typedef  TYPE_1__ ASYNC_WAIT_CTX ;

/* Variables and functions */

int ASYNC_WAIT_CTX_get_all_fds(ASYNC_WAIT_CTX *ctx, OSSL_ASYNC_FD *fd,
                               size_t *numfds)
{
    struct fd_lookup_st *curr;

    curr = ctx->fds;
    *numfds = 0;
    while (curr != NULL) {
        if (curr->del) {
            /* This one has been marked deleted so do nothing */
            curr = curr->next;
            continue;
        }
        if (fd != NULL) {
            *fd = curr->fd;
            fd++;
        }
        (*numfds)++;
        curr = curr->next;
    }
    return 1;
}
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
struct fd_lookup_st {struct fd_lookup_st* next; int /*<<< orphan*/  custom_data; int /*<<< orphan*/  fd; int /*<<< orphan*/  key; int /*<<< orphan*/  (* cleanup ) (struct fd_lookup_st*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  del; struct fd_lookup_st* fds; } ;
typedef  struct fd_lookup_st ASYNC_WAIT_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (struct fd_lookup_st*) ; 
 int /*<<< orphan*/  stub1 (struct fd_lookup_st*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ASYNC_WAIT_CTX_free(ASYNC_WAIT_CTX *ctx)
{
    struct fd_lookup_st *curr;
    struct fd_lookup_st *next;

    if (ctx == NULL)
        return;

    curr = ctx->fds;
    while (curr != NULL) {
        if (!curr->del) {
            /* Only try and cleanup if it hasn't been marked deleted */
            if (curr->cleanup != NULL)
                curr->cleanup(ctx, curr->key, curr->fd, curr->custom_data);
        }
        /* Always free the fd_lookup_st */
        next = curr->next;
        OPENSSL_free(curr);
        curr = next;
    }

    OPENSSL_free(ctx);
}
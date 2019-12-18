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
struct fd_lookup_st {struct fd_lookup_st* next; scalar_t__ add; scalar_t__ del; } ;
struct TYPE_3__ {struct fd_lookup_st* fds; scalar_t__ numdel; scalar_t__ numadd; } ;
typedef  TYPE_1__ ASYNC_WAIT_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (struct fd_lookup_st*) ; 

void async_wait_ctx_reset_counts(ASYNC_WAIT_CTX *ctx)
{
    struct fd_lookup_st *curr, *prev = NULL;

    ctx->numadd = 0;
    ctx->numdel = 0;

    curr = ctx->fds;

    while (curr != NULL) {
        if (curr->del) {
            if (prev == NULL)
                ctx->fds = curr->next;
            else
                prev->next = curr->next;
            OPENSSL_free(curr);
            if (prev == NULL)
                curr = ctx->fds;
            else
                curr = prev->next;
            continue;
        }
        if (curr->add) {
            curr->add = 0;
        }
        prev = curr;
        curr = curr->next;
    }
}
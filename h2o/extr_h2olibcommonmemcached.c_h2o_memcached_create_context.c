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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
struct TYPE_7__ {int /*<<< orphan*/  base; } ;
struct TYPE_6__ {int text_protocol; TYPE_2__ prefix; int /*<<< orphan*/  port; int /*<<< orphan*/  host; scalar_t__ num_threads_connected; int /*<<< orphan*/  pending; int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ h2o_memcached_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  h2o_linklist_init_anchor (int /*<<< orphan*/ *) ; 
 TYPE_1__* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  h2o_multithread_create_thread (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__ h2o_strdup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_main ; 

h2o_memcached_context_t *h2o_memcached_create_context(const char *host, uint16_t port, int text_protocol, size_t num_threads,
                                                      const char *prefix)
{
    h2o_memcached_context_t *ctx = h2o_mem_alloc(sizeof(*ctx));

    pthread_mutex_init(&ctx->mutex, NULL);
    pthread_cond_init(&ctx->cond, NULL);
    h2o_linklist_init_anchor(&ctx->pending);
    ctx->num_threads_connected = 0;
    ctx->host = h2o_strdup(NULL, host, SIZE_MAX).base;
    ctx->port = port;
    ctx->text_protocol = text_protocol;
    ctx->prefix = h2o_strdup(NULL, prefix, SIZE_MAX);

    { /* start the threads */
        pthread_t tid;
        pthread_attr_t attr;
        size_t i;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, 1);
        for (i = 0; i != num_threads; ++i)
            h2o_multithread_create_thread(&tid, &attr, thread_main, ctx);
        pthread_attr_destroy(&attr);
    }

    return ctx;
}
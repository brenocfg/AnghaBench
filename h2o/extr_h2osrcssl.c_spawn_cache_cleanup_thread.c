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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  cache_cleanup_thread ; 
 int /*<<< orphan*/ ** h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  h2o_memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  h2o_multithread_create_thread (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void spawn_cache_cleanup_thread(SSL_CTX **_contexts, size_t num_contexts)
{
    /* copy the list of contexts */
    SSL_CTX **contexts = h2o_mem_alloc(sizeof(*contexts) * (num_contexts + 1));
    h2o_memcpy(contexts, _contexts, sizeof(*contexts) * num_contexts);
    contexts[num_contexts] = NULL;

    /* launch the thread */
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, 1);
    h2o_multithread_create_thread(&tid, &attr, cache_cleanup_thread, contexts);
}
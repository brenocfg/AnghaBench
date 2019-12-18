#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_4__ {void* loop; void* queue; int /*<<< orphan*/  shutdown_receiver; int /*<<< orphan*/  pong_receiver; int /*<<< orphan*/  received_shutdown; } ;
struct TYPE_3__ {void* loop; void* queue; int /*<<< orphan*/  ping_receiver; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT32_MAX ; 
 int /*<<< orphan*/  UV_RUN_ONCE ; 
 void* create_loop () ; 
 int /*<<< orphan*/  destroy_loop (void*) ; 
 int /*<<< orphan*/  h2o_evloop_run (void*,int /*<<< orphan*/ ) ; 
 void* h2o_multithread_create_queue (void*) ; 
 int /*<<< orphan*/  h2o_multithread_destroy_queue (void*) ; 
 int /*<<< orphan*/  h2o_multithread_register_receiver (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_multithread_unregister_receiver (void*,int /*<<< orphan*/ *) ; 
 TYPE_2__ main_thread ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  on_ping ; 
 int /*<<< orphan*/  on_pong ; 
 int /*<<< orphan*/  on_shutdown ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_empty_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_run (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  worker_main ; 
 TYPE_1__ worker_thread ; 

void test_lib__common__multithread_c(void)
{
    pthread_t tid;

    main_thread.loop = create_loop();
    main_thread.queue = h2o_multithread_create_queue(main_thread.loop);
    h2o_multithread_register_receiver(main_thread.queue, &main_thread.pong_receiver, on_pong);
    h2o_multithread_register_receiver(main_thread.queue, &main_thread.shutdown_receiver, on_shutdown);
    worker_thread.loop = create_loop();
    worker_thread.queue = h2o_multithread_create_queue(worker_thread.loop);
    h2o_multithread_register_receiver(worker_thread.queue, &worker_thread.ping_receiver, on_ping);

    pthread_create(&tid, NULL, worker_main, NULL);

    /* send first message */
    send_empty_message(&worker_thread.ping_receiver);

    while (!main_thread.received_shutdown) {
#if H2O_USE_LIBUV
        uv_run(main_thread.loop, UV_RUN_ONCE);
#else
        h2o_evloop_run(main_thread.loop, INT32_MAX);
#endif
    }

    pthread_join(tid, NULL);

    h2o_multithread_unregister_receiver(worker_thread.queue, &worker_thread.ping_receiver);
    h2o_multithread_destroy_queue(worker_thread.queue);
    destroy_loop(worker_thread.loop);
    h2o_multithread_unregister_receiver(main_thread.queue, &main_thread.pong_receiver);
    h2o_multithread_unregister_receiver(main_thread.queue, &main_thread.shutdown_receiver);
    h2o_multithread_destroy_queue(main_thread.queue);
    destroy_loop(main_thread.loop);

    ok(1);
}
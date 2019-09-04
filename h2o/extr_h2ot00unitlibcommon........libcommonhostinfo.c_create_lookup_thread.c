#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {scalar_t__ num_threads; int /*<<< orphan*/  num_threads_idle; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_error_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_strerror_r (int,char*,int) ; 
 int /*<<< orphan*/  lookup_thread_main ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_attr_setstacksize (int /*<<< orphan*/ *,int) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ queue ; 

__attribute__((used)) static void create_lookup_thread(void)
{
    pthread_t tid;
    pthread_attr_t attr;
    int ret;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, 1);
    pthread_attr_setstacksize(&attr, 100 * 1024);
    if ((ret = pthread_create(&tid, NULL, lookup_thread_main, NULL)) != 0) {
        char buf[128];
        if (queue.num_threads == 0) {
            h2o_fatal("failed to start first thread for getaddrinfo: %s", h2o_strerror_r(ret, buf, sizeof(buf)));
        } else {
            h2o_error_printf("pthread_create(for getaddrinfo): %s", h2o_strerror_r(ret, buf, sizeof(buf)));
        }
        return;
    }

    ++queue.num_threads;
    ++queue.num_threads_idle;
}
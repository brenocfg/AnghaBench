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
typedef  int /*<<< orphan*/  uv_cond_t ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int pthread_cond_timedwait_relative_np (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 scalar_t__ pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void uv_cond_destroy(uv_cond_t* cond) {
#if defined(__APPLE__) && defined(__MACH__)
  /* It has been reported that destroying condition variables that have been
   * signalled but not waited on can sometimes result in application crashes.
   * See https://codereview.chromium.org/1323293005.
   */
  pthread_mutex_t mutex;
  struct timespec ts;
  int err;

  if (pthread_mutex_init(&mutex, NULL))
    abort();

  if (pthread_mutex_lock(&mutex))
    abort();

  ts.tv_sec = 0;
  ts.tv_nsec = 1;

  err = pthread_cond_timedwait_relative_np(cond, &mutex, &ts);
  if (err != 0 && err != ETIMEDOUT)
    abort();

  if (pthread_mutex_unlock(&mutex))
    abort();

  if (pthread_mutex_destroy(&mutex))
    abort();
#endif /* defined(__APPLE__) && defined(__MACH__) */

  if (pthread_cond_destroy(cond))
    abort();
}
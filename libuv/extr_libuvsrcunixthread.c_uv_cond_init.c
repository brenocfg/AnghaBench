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
typedef  int /*<<< orphan*/  pthread_condattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int UV__ERR (int) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_condattr_destroy (int /*<<< orphan*/ *) ; 
 int pthread_condattr_init (int /*<<< orphan*/ *) ; 
 int pthread_condattr_setclock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int uv_cond_init(uv_cond_t* cond) {
  pthread_condattr_t attr;
  int err;

  err = pthread_condattr_init(&attr);
  if (err)
    return UV__ERR(err);

#if !(defined(__ANDROID_API__) && __ANDROID_API__ < 21)
  err = pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);
  if (err)
    goto error2;
#endif

  err = pthread_cond_init(cond, &attr);
  if (err)
    goto error2;

  err = pthread_condattr_destroy(&attr);
  if (err)
    goto error;

  return 0;

error:
  pthread_cond_destroy(cond);
error2:
  pthread_condattr_destroy(&attr);
  return UV__ERR(err);
}
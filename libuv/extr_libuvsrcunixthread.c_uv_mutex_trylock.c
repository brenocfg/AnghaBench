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
typedef  int /*<<< orphan*/  uv_mutex_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int UV_EBUSY ; 
 int /*<<< orphan*/  abort () ; 
 int pthread_mutex_trylock (int /*<<< orphan*/ *) ; 

int uv_mutex_trylock(uv_mutex_t* mutex) {
  int err;

  err = pthread_mutex_trylock(mutex);
  if (err) {
    if (err != EBUSY && err != EAGAIN)
      abort();
    return UV_EBUSY;
  }

  return 0;
}
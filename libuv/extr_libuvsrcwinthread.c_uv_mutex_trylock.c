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
 scalar_t__ TryEnterCriticalSection (int /*<<< orphan*/ *) ; 
 int UV_EBUSY ; 

int uv_mutex_trylock(uv_mutex_t* mutex) {
  if (TryEnterCriticalSection(mutex))
    return 0;
  else
    return UV_EBUSY;
}
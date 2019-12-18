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
struct TYPE_3__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  TYPE_1__ uv_timeval64_t ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int UV_EINVAL ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

int uv_gettimeofday(uv_timeval64_t* tv) {
  struct timeval time;

  if (tv == NULL)
    return UV_EINVAL;

  if (gettimeofday(&time, NULL) != 0)
    return UV__ERR(errno);

  tv->tv_sec = (int64_t) time.tv_sec;
  tv->tv_usec = (int32_t) time.tv_usec;
  return 0;
}
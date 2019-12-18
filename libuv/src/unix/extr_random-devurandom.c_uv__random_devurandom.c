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

/* Variables and functions */
 int /*<<< orphan*/  once ; 
 scalar_t__ status ; 
 int /*<<< orphan*/  uv__random_devurandom_init ; 
 int uv__random_readpath (char*,void*,size_t) ; 
 int /*<<< orphan*/  uv_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int uv__random_devurandom(void* buf, size_t buflen) {
  uv_once(&once, uv__random_devurandom_init);

  if (status != 0)
    return status;

  return uv__random_readpath("/dev/urandom", buf, buflen);
}
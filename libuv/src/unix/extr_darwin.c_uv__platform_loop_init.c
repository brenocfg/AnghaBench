#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * cf_state; } ;
typedef  TYPE_1__ uv_loop_t ;

/* Variables and functions */
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ uv__kqueue_init (TYPE_1__*) ; 

int uv__platform_loop_init(uv_loop_t* loop) {
  loop->cf_state = NULL;

  if (uv__kqueue_init(loop))
    return UV__ERR(errno);

  return 0;
}
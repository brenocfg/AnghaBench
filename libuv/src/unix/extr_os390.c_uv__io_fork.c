#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * ep; } ;
typedef  TYPE_1__ uv_loop_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv__platform_loop_delete (TYPE_1__*) ; 
 int uv__platform_loop_init (TYPE_1__*) ; 

int uv__io_fork(uv_loop_t* loop) {
  /*
    Nullify the msg queue but don't close it because
    it is still being used by the parent.
  */
  loop->ep = NULL;

  uv__platform_loop_delete(loop);
  return uv__platform_loop_init(loop);
}
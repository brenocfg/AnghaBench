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
struct TYPE_4__ {scalar_t__ ran; } ;
typedef  TYPE_1__ uv_once_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv__once_inner (TYPE_1__*,void (*) ()) ; 

void uv_once(uv_once_t* guard, void (*callback)(void)) {
  /* Fast case - avoid WaitForSingleObject. */
  if (guard->ran) {
    return;
  }

  uv__once_inner(guard, callback);
}
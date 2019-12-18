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
struct TYPE_3__ {int /*<<< orphan*/  pending; } ;
typedef  TYPE_1__ uv_async_t ;

/* Variables and functions */
 int cmpxchgi (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static int uv__async_spin(uv_async_t* handle) {
  int rc;

  for (;;) {
    /* rc=0 -- handle is not pending.
     * rc=1 -- handle is pending, other thread is still working with it.
     * rc=2 -- handle is pending, other thread is done.
     */
    rc = cmpxchgi(&handle->pending, 2, 0);

    if (rc != 1)
      return rc;

    /* Other thread is busy with this handle, spin until it's done. */
    cpu_relax();
  }
}
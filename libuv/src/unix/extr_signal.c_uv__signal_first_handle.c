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
struct TYPE_5__ {int signum; int /*<<< orphan*/ * loop; scalar_t__ flags; } ;
typedef  TYPE_1__ uv_signal_t ;

/* Variables and functions */
 TYPE_1__* RB_NFIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  uv__signal_tree ; 
 int /*<<< orphan*/  uv__signal_tree_s ; 

__attribute__((used)) static uv_signal_t* uv__signal_first_handle(int signum) {
  /* This function must be called with the signal lock held. */
  uv_signal_t lookup;
  uv_signal_t* handle;

  lookup.signum = signum;
  lookup.flags = 0;
  lookup.loop = NULL;

  handle = RB_NFIND(uv__signal_tree_s, &uv__signal_tree, &lookup);

  if (handle != NULL && handle->signum == signum)
    return handle;

  return NULL;
}
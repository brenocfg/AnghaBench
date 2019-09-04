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
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int USER_LOADED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unload_user_metafile (TYPE_1__*) ; 

void user_unload (user *u) {
  assert (u != NULL);
  if (!(u->flags & USER_LOADED)) {
    assert (0);
    return;
  }

  u->flags ^= USER_LOADED;
  unload_user_metafile (u);
}
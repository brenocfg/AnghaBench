#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * metafile; } ;
typedef  TYPE_1__ user ;
struct TYPE_7__ {int user_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/ * EMPTY__METAFILE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,TYPE_1__*) ; 
 TYPE_3__ header ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_1__* users ; 
 int verbosity ; 

void bind_user_metafile (user *u) {
  if (verbosity > 2) {
    fprintf (stderr, "bind user metafile local id = %d (%p)\n", (int)(u - users), u);
  }
  int local_id = (int)(u - users);

  if (u->metafile == NULL || u->metafile == EMPTY__METAFILE) {
    return;
  }

  assert (1 <= local_id && local_id <= header.user_cnt);
}
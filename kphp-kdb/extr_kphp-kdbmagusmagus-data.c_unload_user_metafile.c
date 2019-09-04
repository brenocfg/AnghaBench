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
struct TYPE_5__ {int id; scalar_t__ metafile_len; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int /*<<< orphan*/  allocated_metafile_bytes ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unbind_user_metafile (TYPE_1__*) ; 
 int /*<<< orphan*/  user_loaded (TYPE_1__*) ; 
 int verbosity ; 

int unload_user_metafile (user *u) {
  assert (u != NULL);

  int user_id = 0;

  if (verbosity > 1) {
    user_id = u->id;
  }

  if (verbosity > 2) {
    fprintf (stderr, "unload_user_metafile (%d)\n", user_id);
  }

  if (!u || !user_loaded (u)) {
    if (verbosity > 1) {
      fprintf (stderr, "cannot unload user metafile (%d)\n", user_id);
      assert (0);
    }
    return 0;
  }

  allocated_metafile_bytes -= u->metafile_len;

  unbind_user_metafile (u);

  if (verbosity > 2) {
    fprintf (stderr, "unload_user_metafile (%d) END\n", user_id);
  }

  return 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* metafile; int /*<<< orphan*/ * aio; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int /*<<< orphan*/  add_user_used (TYPE_1__*) ; 
 int /*<<< orphan*/  del_user_used (TYPE_1__*) ; 
 int /*<<< orphan*/  user_apply_changes (TYPE_1__*) ; 

inline char *get_user_metafile (user *u) {
  if (u->aio != NULL || u->metafile == NULL) {
    return NULL;
  }

  user_apply_changes (u);

  del_user_used (u);
  add_user_used (u);

  return u->metafile;
}
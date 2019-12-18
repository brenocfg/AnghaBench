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
struct TYPE_3__ {int metafile_len; int /*<<< orphan*/  sugg; int /*<<< orphan*/  new_exceptions; int /*<<< orphan*/ * prev_used; int /*<<< orphan*/ * next_used; int /*<<< orphan*/ * aio; int /*<<< orphan*/ * metafile; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int /*<<< orphan*/  CHG_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trp_init (int /*<<< orphan*/ *) ; 

void user_init (user *u) {
  u->metafile = NULL;
  u->metafile_len = -1;
  u->aio = NULL;
  u->next_used = NULL;
  u->prev_used = NULL;

  CHG_INIT (u->new_exceptions);
  trp_init (&u->sugg);
}
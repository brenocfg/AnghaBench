#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cnt; scalar_t__ nbad; scalar_t__ ngood; } ;
struct TYPE_5__ {int metafile_len; TYPE_1__ b; int /*<<< orphan*/ * prev_used; int /*<<< orphan*/ * next_used; int /*<<< orphan*/ * aio; int /*<<< orphan*/ * metafile; } ;
typedef  TYPE_2__ user ;

/* Variables and functions */
 int /*<<< orphan*/  qhtbl_init (int /*<<< orphan*/ *) ; 

void user_init (user *u) {
  u->metafile = NULL;
  u->metafile_len = -1;
  u->aio = NULL;
  u->next_used = NULL;
  u->prev_used = NULL;

  u->b.ngood = 0;
  u->b.nbad = 0;
  qhtbl_init (&u->b.cnt);
}
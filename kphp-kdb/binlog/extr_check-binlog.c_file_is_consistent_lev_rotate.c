#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* F; } ;
struct TYPE_10__ {TYPE_3__ S; int /*<<< orphan*/  rotate_from; int /*<<< orphan*/  rotate_to; } ;
typedef  TYPE_4__ file_t ;
struct TYPE_8__ {TYPE_1__* info; } ;
struct TYPE_7__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_fatal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ match_rotate_logevents (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int file_is_consistent_lev_rotate (file_t *U, file_t *V) {
  if (match_rotate_logevents (&U->rotate_to, &V->rotate_from) <= 0) {
    log_fatal ("'%s' and '%s' have unconsistent LEV_ROTATE_TO and LEV_ROTATE_FROM", U->S.F->info->filename, V->S.F->info->filename);
    return -1;
  }
  return 1;
}
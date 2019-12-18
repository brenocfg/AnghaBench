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
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_2__ rotate_to; int /*<<< orphan*/  S; } ;
typedef  TYPE_1__ file_t ;

/* Variables and functions */
 scalar_t__ LEV_ROTATE_TO ; 
 scalar_t__ stream_read_lev_rotate_to (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int file_binlog_read_lev_rotate_to (file_t *F) {
  if (stream_read_lev_rotate_to (&F->S, &F->rotate_to) < 0) {
    return -1;
  }

  if (F->rotate_to.type != LEV_ROTATE_TO) {
    return -1;
  }

  return 0;
}
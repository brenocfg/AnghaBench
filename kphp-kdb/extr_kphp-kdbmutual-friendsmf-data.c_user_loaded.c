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
struct TYPE_3__ {scalar_t__ metafile_len; int /*<<< orphan*/ * aio; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */

int user_loaded (user *u) {
  return u->metafile_len >= 0 && u->aio == NULL;
}
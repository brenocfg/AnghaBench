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
struct TYPE_3__ {int /*<<< orphan*/  const t_cursor; } ;
typedef  TYPE_1__ teken_t ;
typedef  int /*<<< orphan*/  teken_pos_t ;

/* Variables and functions */

const teken_pos_t *
teken_get_cursor(const teken_t *t)
{

	return (&t->t_cursor);
}
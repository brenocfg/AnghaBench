#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tunable_quad {int /*<<< orphan*/  var; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNABLE_QUAD_FETCH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tunable_quad_init(void *data)
{
	struct tunable_quad *d = (struct tunable_quad *)data;

	TUNABLE_QUAD_FETCH(d->path, d->var);
}
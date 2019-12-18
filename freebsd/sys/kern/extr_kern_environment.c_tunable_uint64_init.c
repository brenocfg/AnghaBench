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
struct tunable_uint64 {int /*<<< orphan*/  var; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNABLE_UINT64_FETCH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tunable_uint64_init(void *data)
{
	struct tunable_uint64 *d = (struct tunable_uint64 *)data;

	TUNABLE_UINT64_FETCH(d->path, d->var);
}
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
struct wmemstream {scalar_t__ len; scalar_t__ offset; scalar_t__* sizep; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
wmemstream_update(struct wmemstream *ms)
{

	assert(ms->len >= 0 && ms->offset >= 0);
	*ms->sizep = ms->len < ms->offset ? ms->len : ms->offset;
}
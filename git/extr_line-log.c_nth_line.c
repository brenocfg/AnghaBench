#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nth_line_cb {long lines; int* line_ends; TYPE_1__* spec; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static const char *nth_line(void *data, long line)
{
	struct nth_line_cb *d = data;
	assert(d && line <= d->lines);
	assert(d->spec && d->spec->data);

	if (line == 0)
		return (char *)d->spec->data;
	else
		return (char *)d->spec->data + d->line_ends[line] + 1;
}
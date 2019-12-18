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
struct TYPE_2__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ filesystem_iterator_entry ;

/* Variables and functions */
 int git__strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filesystem_iterator_entry_cmp_icase(const void *_a, const void *_b)
{
	const filesystem_iterator_entry *a = (const filesystem_iterator_entry *)_a;
	const filesystem_iterator_entry *b = (const filesystem_iterator_entry *)_b;

	return git__strcasecmp(a->path, b->path);
}
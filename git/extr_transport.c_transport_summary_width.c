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
struct ref {int /*<<< orphan*/  new_oid; int /*<<< orphan*/  old_oid; struct ref* next; } ;

/* Variables and functions */
 int FALLBACK_DEFAULT_ABBREV ; 
 int measure_abbrev (int /*<<< orphan*/ *,int) ; 

int transport_summary_width(const struct ref *refs)
{
	int maxw = -1;

	for (; refs; refs = refs->next) {
		maxw = measure_abbrev(&refs->old_oid, maxw);
		maxw = measure_abbrev(&refs->new_oid, maxw);
	}
	if (maxw < 0)
		maxw = FALLBACK_DEFAULT_ABBREV;
	return (2 * maxw + 3);
}
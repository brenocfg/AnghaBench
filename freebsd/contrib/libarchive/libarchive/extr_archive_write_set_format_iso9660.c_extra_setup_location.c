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
struct TYPE_2__ {struct extr_rec* current; struct extr_rec* first; } ;
struct isoent {TYPE_1__ extr_rec_list; } ;
struct extr_rec {struct extr_rec* next; scalar_t__ offset; int /*<<< orphan*/  location; } ;

/* Variables and functions */

__attribute__((used)) static int
extra_setup_location(struct isoent *isoent, int location)
{
	struct extr_rec *rec;
	int cnt;

	cnt = 0;
	rec = isoent->extr_rec_list.first;
	isoent->extr_rec_list.current = rec;
	while (rec) {
		cnt++;
		rec->location = location++;
		rec->offset = 0;
		rec = rec->next;
	}
	return (cnt);
}
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
struct cdeque {scalar_t__ end_pos; scalar_t__ beg_pos; scalar_t__ size; } ;

/* Variables and functions */

__attribute__((used)) static void cdeque_clear(struct cdeque* d) {
	d->size = 0;
	d->beg_pos = 0;
	d->end_pos = 0;
}
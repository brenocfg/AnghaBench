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
struct TYPE_2__ {int /*<<< orphan*/  filters; } ;
struct rar5 {TYPE_1__ cstate; } ;
struct filter_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  cdeque_filter (struct filter_info*) ; 
 int /*<<< orphan*/  cdeque_push_back (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct filter_info* add_new_filter(struct rar5* rar) {
	struct filter_info* f =
		(struct filter_info*) calloc(1, sizeof(struct filter_info));

	if(!f) {
		return NULL;
	}

	cdeque_push_back(&rar->cstate.filters, cdeque_filter(f));
	return f;
}
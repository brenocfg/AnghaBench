#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  filters; struct rar5* filtered_buf; struct rar5* window_buf; } ;
struct TYPE_4__ {struct rar5* push_buf; } ;
struct rar5 {TYPE_2__ cstate; TYPE_1__ vol; } ;
struct archive_read {TYPE_3__* format; } ;
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  cdeque_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct rar5*) ; 
 int /*<<< orphan*/  free_filters (struct rar5*) ; 
 struct rar5* get_context (struct archive_read*) ; 

__attribute__((used)) static int rar5_cleanup(struct archive_read *a) {
	struct rar5* rar = get_context(a);

	free(rar->cstate.window_buf);
	free(rar->cstate.filtered_buf);

	free(rar->vol.push_buf);

	free_filters(rar);
	cdeque_free(&rar->cstate.filters);

	free(rar);
	a->format->data = NULL;

	return ARCHIVE_OK;
}
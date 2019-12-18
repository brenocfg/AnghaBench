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
struct TYPE_2__ {struct qentry* dat; } ;
struct qentry {TYPE_1__ data; } ;

/* Variables and functions */
 struct qentry* dequeue () ; 
 int /*<<< orphan*/  free (struct qentry*) ; 
 int /*<<< orphan*/  grep_printline (TYPE_1__*,char) ; 

void
printqueue(void)
{
	struct qentry *item;

	while ((item = dequeue()) != NULL) {
		grep_printline(&item->data, '-');
		free(item->data.dat);
		free(item);
	}
}
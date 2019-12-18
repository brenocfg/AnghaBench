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
struct TYPE_2__ {struct discovery* oid; } ;
struct discovery {struct discovery* service; int /*<<< orphan*/  refs; struct discovery* buf_alloc; TYPE_1__ shallow; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct discovery*) ; 
 int /*<<< orphan*/  free_refs (int /*<<< orphan*/ ) ; 
 struct discovery* last_discovery ; 

__attribute__((used)) static void free_discovery(struct discovery *d)
{
	if (d) {
		if (d == last_discovery)
			last_discovery = NULL;
		free(d->shallow.oid);
		free(d->buf_alloc);
		free_refs(d->refs);
		free(d->service);
		free(d);
	}
}
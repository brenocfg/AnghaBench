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
struct gkc_tuple {int dummy; } ;
struct gkc_summary {struct freelist* fl; int /*<<< orphan*/  alloced; } ;
struct freelist {struct freelist* next; } ;

/* Variables and functions */

__attribute__((used)) static void gkc_free(struct gkc_summary *s, struct gkc_tuple *p)
{
    struct freelist *flp = (void *)p;
    s->alloced--;

    flp->next = s->fl;
    s->fl = flp;
}
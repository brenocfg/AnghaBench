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
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct ohash {int /*<<< orphan*/ * t; TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ohash_delete(struct ohash *h)
{
	(h->info.free)(h->t, h->info.data);
#ifndef NDEBUG
	h->t = NULL;
#endif
}
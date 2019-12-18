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
struct mtx {int dummy; } ;
struct knlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  knlist_init (struct knlist*,struct mtx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
knlist_init_mtx(struct knlist *knl, struct mtx *lock)
{

	knlist_init(knl, lock, NULL, NULL, NULL, NULL);
}
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
struct knote {int dummy; } ;
struct knlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  knlist_remove_kq (struct knlist*,struct knote*,int,int /*<<< orphan*/ ) ; 

void
knlist_remove(struct knlist *knl, struct knote *kn, int islocked)
{

	knlist_remove_kq(knl, kn, islocked, 0);
}
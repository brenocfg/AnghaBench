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
 int /*<<< orphan*/  M_KQUEUE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  knlist_init_mtx (struct knlist*,struct mtx*) ; 
 struct knlist* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct knlist *
knlist_alloc(struct mtx *lock)
{
	struct knlist *knl;

	knl = malloc(sizeof(struct knlist), M_KQUEUE, M_WAITOK);
	knlist_init_mtx(knl, lock);
	return (knl);
}
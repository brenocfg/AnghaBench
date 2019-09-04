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
struct oidset_iter {int dummy; } ;
struct oidset {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  oidset_iter_init (struct oidset*,struct oidset_iter*) ; 
 struct object_id* oidset_iter_next (struct oidset_iter*) ; 

__attribute__((used)) static inline struct object_id *oidset_iter_first(struct oidset *set,
						  struct oidset_iter *iter)
{
	oidset_iter_init(set, iter);
	return oidset_iter_next(iter);
}
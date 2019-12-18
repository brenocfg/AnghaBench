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
struct oidset_iter {int /*<<< orphan*/ * set; int /*<<< orphan*/  iter; } ;
struct oidset {int /*<<< orphan*/  set; } ;

/* Variables and functions */
 int /*<<< orphan*/  kh_begin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void oidset_iter_init(struct oidset *set,
				    struct oidset_iter *iter)
{
	iter->set = &set->set;
	iter->iter = kh_begin(iter->set);
}
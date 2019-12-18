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
struct filemon {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline struct filemon *
filemon_acquire(struct filemon *filemon)
{

	if (filemon != NULL)
		refcount_acquire(&filemon->refcnt);
	return (filemon);
}
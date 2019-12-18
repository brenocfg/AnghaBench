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
struct label {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ SLOT (struct label*) ; 
 scalar_t__ partition_enabled ; 

__attribute__((used)) static int
partition_check(struct label *subject, struct label *object)
{

	if (partition_enabled == 0)
		return (0);

	if (subject == NULL)
		return (0);

	if (SLOT(subject) == 0)
		return (0);

	/*
	 * If the object label hasn't been allocated, then it's effectively
	 * not in a partition, and we know the subject is as it has a label
	 * and it's not 0, so reject.
	 */
	if (object == NULL)
		return (EPERM);

	if (SLOT(subject) == SLOT(object))
		return (0);

	return (EPERM);
}
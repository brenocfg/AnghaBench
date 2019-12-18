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
struct cpuset {int dummy; } ;
typedef  int cpusetid_t ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int ENFILE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int _cpuset_create (struct cpuset*,struct cpuset*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int alloc_unr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuset_unr ; 
 int /*<<< orphan*/  cpuset_zone ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int) ; 
 struct cpuset* uma_zalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct cpuset*) ; 

__attribute__((used)) static int
cpuset_create(struct cpuset **setp, struct cpuset *parent, const cpuset_t *mask)
{
	struct cpuset *set;
	cpusetid_t id;
	int error;

	id = alloc_unr(cpuset_unr);
	if (id == -1)
		return (ENFILE);
	*setp = set = uma_zalloc(cpuset_zone, M_WAITOK | M_ZERO);
	error = _cpuset_create(set, parent, mask, NULL, id);
	if (error == 0)
		return (0);
	free_unr(cpuset_unr, id);
	uma_zfree(cpuset_zone, set);

	return (error);
}
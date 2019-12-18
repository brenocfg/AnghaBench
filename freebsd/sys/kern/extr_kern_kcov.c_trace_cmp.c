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
typedef  int uint64_t ;
struct thread {int dummy; } ;
struct kcov_info {scalar_t__ mode; scalar_t__ kvaddr; int entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ KCOV_MODE_TRACE_CMP ; 
 scalar_t__ atomic_cmpset_64 (int*,int,int) ; 
 struct thread* curthread ; 
 struct kcov_info* get_kinfo (struct thread*) ; 

__attribute__((used)) static bool
trace_cmp(uint64_t type, uint64_t arg1, uint64_t arg2, uint64_t ret)
{
	struct thread *td;
	struct kcov_info *info;
	uint64_t *buf, index;

	td = curthread;
	info = get_kinfo(td);
	if (info == NULL)
		return (false);

	/*
	 * Check we are in the comparison-trace mode.
	 */
	if (info->mode != KCOV_MODE_TRACE_CMP)
		return (false);

	KASSERT(info->kvaddr != 0,
	    ("__sanitizer_cov_trace_pc: NULL buf while running"));

	buf = (uint64_t *)info->kvaddr;

	/* The first entry of the buffer holds the index */
	index = buf[0];

	/* Check we have space to store all elements */
	if (index * 4 + 4 + 1 > info->entries)
		return (false);

	while (1) {
		buf[index * 4 + 1] = type;
		buf[index * 4 + 2] = arg1;
		buf[index * 4 + 3] = arg2;
		buf[index * 4 + 4] = ret;

		if (atomic_cmpset_64(&buf[0], index, index + 1))
			break;
		buf[0] = index;
	}

	return (true);
}
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
typedef  int /*<<< orphan*/  uint64_t ;
struct mem_range {int (* handler ) (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  arg2; int /*<<< orphan*/  arg1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_F_READ ; 
 int stub1 (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mem_read(void *ctx, int vcpu, uint64_t gpa, uint64_t *rval, int size, void *arg)
{
	int error;
	struct mem_range *mr = arg;

	error = (*mr->handler)(ctx, vcpu, MEM_F_READ, gpa, size,
			       rval, mr->arg1, mr->arg2);
	return (error);
}
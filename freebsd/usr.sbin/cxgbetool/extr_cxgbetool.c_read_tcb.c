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
typedef  long long uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_CMM_TCB_BASE ; 
 int EINVAL ; 
 unsigned int TCB_SIZE ; 
 int read_mem (long long,unsigned int,int /*<<< orphan*/ ) ; 
 int read_reg (int /*<<< orphan*/ ,int,long long*) ; 
 int /*<<< orphan*/  show_tcb ; 
 char* str_to_number (char const*,long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
read_tcb(int argc, const char *argv[])
{
	char *p;
	long l;
	long long val;
	unsigned int tid;
	uint32_t addr;
	int rc;

	if (argc != 1) {
		warnx("incorrect number of arguments.");
		return (EINVAL);
	}

	p = str_to_number(argv[0], &l, NULL);
	if (*p) {
		warnx("invalid tid \"%s\"", argv[0]);
		return (EINVAL);
	}
	tid = l;

	rc = read_reg(A_TP_CMM_TCB_BASE, 4, &val);
	if (rc != 0)
		return (rc);

	addr = val + tid * TCB_SIZE;

	return (read_mem(addr, TCB_SIZE, show_tcb));
}
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
typedef  int uint32_t ;
struct ch_mem_range {unsigned int addr; unsigned int len; scalar_t__ buf; int /*<<< orphan*/  mem_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_GET_MEM ; 
 int /*<<< orphan*/  MEM_CM ; 
 unsigned int TCB_SIZE ; 
 scalar_t__ calloc (int,unsigned int) ; 
 scalar_t__ doit (char const*,int /*<<< orphan*/ ,struct ch_mem_range*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ get_int_arg (char*,unsigned int*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static int
get_tcb2(int argc, char *argv[], int start_arg, const char *iff_name)
{
	uint64_t *d;
	unsigned int i;
	unsigned int tcb_idx;
	struct ch_mem_range mr;

	if (argc != start_arg + 1)
		return -1;

	if (get_int_arg(argv[start_arg], &tcb_idx))
		return -1;

	mr.buf = calloc(1, TCB_SIZE);
	if (!mr.buf)
		err(1, "get TCB");

	mr.mem_id = MEM_CM;
	mr.addr   = tcb_idx * TCB_SIZE;
	mr.len    = TCB_SIZE;

	if (doit(iff_name, CHELSIO_GET_MEM, &mr) < 0)
		err(1, "get TCB");

	for (d = (uint64_t *)mr.buf, i = 0; i < TCB_SIZE / 32; i++) {
		printf("%2u:", i);
		printf(" %08x %08x %08x %08x", (uint32_t)d[1],
		       (uint32_t)(d[1] >> 32), (uint32_t)d[0],
		       (uint32_t)(d[0] >> 32));
		d += 2;
		printf(" %08x %08x %08x %08x\n", (uint32_t)d[1],
		       (uint32_t)(d[1] >> 32), (uint32_t)d[0],
		       (uint32_t)(d[0] >> 32));
		d += 2;
	}
	free(mr.buf);
	return 0;
}
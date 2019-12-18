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
typedef  void* uint32_t ;
struct t4_mem_range {void* len; scalar_t__ data; void* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_T4_GET_MEM ; 
 int doit (int /*<<< orphan*/ ,struct t4_mem_range*) ; 
 int errno ; 
 int /*<<< orphan*/  free (void**) ; 
 scalar_t__ malloc (void*) ; 
 void stub1 (void**,void*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
read_mem(uint32_t addr, uint32_t len, void (*output)(uint32_t *, uint32_t))
{
	int rc;
	struct t4_mem_range mr;

	mr.addr = addr;
	mr.len = len;
	mr.data = malloc(mr.len);

	if (mr.data == 0) {
		warn("read_mem: malloc");
		return (errno);
	}

	rc = doit(CHELSIO_T4_GET_MEM, &mr);
	if (rc != 0)
		goto done;

	if (output)
		(*output)(mr.data, mr.len);
done:
	free(mr.data);
	return (rc);
}
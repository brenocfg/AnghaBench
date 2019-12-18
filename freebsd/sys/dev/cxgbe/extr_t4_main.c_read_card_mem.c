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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct t4_mem_range {scalar_t__ data; scalar_t__ len; scalar_t__ addr; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_READ_BUF_SIZE ; 
 int /*<<< orphan*/  M_CXGBE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int copyout (scalar_t__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  free (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__* malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_via_memwin (struct adapter*,int,scalar_t__,scalar_t__*,scalar_t__) ; 
 int validate_mem_range (struct adapter*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
read_card_mem(struct adapter *sc, int win, struct t4_mem_range *mr)
{
	uint32_t addr, remaining, n;
	uint32_t *buf;
	int rc;
	uint8_t *dst;

	rc = validate_mem_range(sc, mr->addr, mr->len);
	if (rc != 0)
		return (rc);

	buf = malloc(min(mr->len, MAX_READ_BUF_SIZE), M_CXGBE, M_WAITOK);
	addr = mr->addr;
	remaining = mr->len;
	dst = (void *)mr->data;

	while (remaining) {
		n = min(remaining, MAX_READ_BUF_SIZE);
		read_via_memwin(sc, 2, addr, buf, n);

		rc = copyout(buf, dst, n);
		if (rc != 0)
			break;

		dst += n;
		remaining -= n;
		addr += n;
	}

	free(buf, M_CXGBE);
	return (rc);
}
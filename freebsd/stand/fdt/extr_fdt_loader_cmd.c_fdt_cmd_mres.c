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

/* Variables and functions */
 int CMD_OK ; 
 int /*<<< orphan*/  fdt_get_mem_rsv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fdt_num_mem_rsv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdtp ; 
 int /*<<< orphan*/  pager_close () ; 
 int /*<<< orphan*/  pager_open () ; 
 scalar_t__ pager_output (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fdt_cmd_mres(int argc, char *argv[])
{
	uint64_t start, size;
	int i, total;
	char line[80];

	pager_open();
	total = fdt_num_mem_rsv(fdtp);
	if (total > 0) {
		if (pager_output("Reserved memory regions:\n"))
			goto out;
		for (i = 0; i < total; i++) {
			fdt_get_mem_rsv(fdtp, i, &start, &size);
			sprintf(line, "reg#%d: (start: 0x%jx, size: 0x%jx)\n", 
			    i, start, size);
			if (pager_output(line))
				goto out;
		}
	} else
		pager_output("No reserved memory regions\n");
out:
	pager_close();

	return (CMD_OK);
}
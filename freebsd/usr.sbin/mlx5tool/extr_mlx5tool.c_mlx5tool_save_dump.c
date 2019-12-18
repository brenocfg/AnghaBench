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
struct mlx5_tool_addr {int dummy; } ;
struct mlx5_fwdump_reg {int addr; int val; } ;
struct mlx5_fwdump_get {size_t reg_filled; size_t reg_cnt; struct mlx5_fwdump_reg* buf; struct mlx5_tool_addr devaddr; } ;
typedef  int /*<<< orphan*/  fdg ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  MLX5_FWDUMP_GET ; 
 struct mlx5_fwdump_reg* calloc (size_t,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct mlx5_fwdump_get*) ; 
 int /*<<< orphan*/  memset (struct mlx5_fwdump_get*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
mlx5tool_save_dump(int ctldev, const struct mlx5_tool_addr *addr,
    const char *dumpname)
{
	struct mlx5_fwdump_get fdg;
	struct mlx5_fwdump_reg *rege;
	FILE *dump;
	size_t cnt;
	int error, res;

	if (dumpname == NULL)
		dump = stdout;
	else
		dump = fopen(dumpname, "w");
	if (dump == NULL) {
		warn("open %s", dumpname);
		return (1);
	}
	res = 1;
	memset(&fdg, 0, sizeof(fdg));
	fdg.devaddr = *addr;
	error = ioctl(ctldev, MLX5_FWDUMP_GET, &fdg);
	if (error != 0) {
		warn("MLX5_FWDUMP_GET dumpsize");
		goto out;
	}
	rege = calloc(fdg.reg_filled, sizeof(*rege));
	if (rege == NULL) {
		warn("alloc rege");
		goto out;
	}
	fdg.buf = rege;
	fdg.reg_cnt = fdg.reg_filled;
	error = ioctl(ctldev, MLX5_FWDUMP_GET, &fdg);
	if (error != 0) {
		if (errno == ENOENT)
			warnx("no dump recorded");
		else
			warn("MLX5_FWDUMP_GET dump fetch");
		goto out;
	}
	for (cnt = 0; cnt < fdg.reg_cnt; cnt++, rege++)
		fprintf(dump, "0x%08x\t0x%08x\n", rege->addr, rege->val);
	res = 0;
out:
	if (dump != stdout)
		fclose(dump);
	return (res);
}
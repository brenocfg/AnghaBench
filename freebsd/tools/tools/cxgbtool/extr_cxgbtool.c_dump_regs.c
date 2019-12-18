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
typedef  int /*<<< orphan*/  uint32_t ;
struct ch_ifconf_regs {int version; int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_IFCONF_GETREGS ; 
 int /*<<< orphan*/  REGDUMP_SIZE ; 
 scalar_t__ doit (char const*,int /*<<< orphan*/ ,struct ch_ifconf_regs*) ; 
 int dump_regs_t2 (int,char**,int,int /*<<< orphan*/ *) ; 
 int dump_regs_t3 (int,char**,int,int /*<<< orphan*/ *,int) ; 
 int dump_regs_t3b (int,char**,int,int /*<<< orphan*/ *,int) ; 
 int dump_regs_t3c (int,char**,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int,int) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dump_regs(int argc, char *argv[], int start_arg, const char *iff_name)
{
	int vers, revision, is_pcie;
	struct ch_ifconf_regs regs;

	regs.len = REGDUMP_SIZE;

	/* XXX: This is never freed.  Looks like we don't care. */
	if ((regs.data = malloc(regs.len)) == NULL)
		err(1, "can't malloc");

	if (doit(iff_name, CHELSIO_IFCONF_GETREGS, &regs))
		err(1, "can't read registers");

	vers = regs.version & 0x3ff;
	revision = (regs.version >> 10) & 0x3f;
	is_pcie = (regs.version & 0x80000000) != 0;

	if (vers <= 2)
		return dump_regs_t2(argc, argv, start_arg, (uint32_t *)regs.data);
#if defined(CONFIG_T3_REGS)
	if (vers == 3) {
		if (revision == 0)
			return dump_regs_t3(argc, argv, start_arg,
					    (uint32_t *)regs.data, is_pcie);
		if (revision == 2 || revision == 3)
			return dump_regs_t3b(argc, argv, start_arg,
					     (uint32_t *)regs.data, is_pcie);
		if (revision == 4)
			return dump_regs_t3c(argc, argv, start_arg,
			    		     (uint32_t *)regs.data, is_pcie);
	}
#endif
	errx(1, "unknown card type %d.%d", vers, revision);
	return 0;
}
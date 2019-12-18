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
struct t4_regdump {int version; int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_T4_REGDUMP ; 
 int ENOMEM ; 
 int ENOTSUP ; 
 int /*<<< orphan*/  T4_REGDUMP_SIZE ; 
 int /*<<< orphan*/  T5_REGDUMP_SIZE ; 
 int /*<<< orphan*/ * calloc (int,int /*<<< orphan*/ ) ; 
 int doit (int /*<<< orphan*/ ,struct t4_regdump*) ; 
 int dump_regs_t4 (int,char const**,int /*<<< orphan*/ *) ; 
 int dump_regs_t4vf (int,char const**,int /*<<< orphan*/ *) ; 
 int dump_regs_t5 (int,char const**,int /*<<< orphan*/ *) ; 
 int dump_regs_t5vf (int,char const**,int /*<<< orphan*/ *) ; 
 int dump_regs_t6 (int,char const**,int /*<<< orphan*/ *) ; 
 int dump_regs_t6vf (int,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int get_card_vers (int) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nexus ; 
 int /*<<< orphan*/  warnc (int,char*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
dump_regs(int argc, const char *argv[])
{
	int vers, revision, rc;
	struct t4_regdump regs;
	uint32_t len;

	len = max(T4_REGDUMP_SIZE, T5_REGDUMP_SIZE);
	regs.data = calloc(1, len);
	if (regs.data == NULL) {
		warnc(ENOMEM, "regdump");
		return (ENOMEM);
	}

	regs.len = len;
	rc = doit(CHELSIO_T4_REGDUMP, &regs);
	if (rc != 0)
		return (rc);

	vers = get_card_vers(regs.version);
	revision = (regs.version >> 10) & 0x3f;

	if (vers == 4) {
		if (revision == 0x3f)
			rc = dump_regs_t4vf(argc, argv, regs.data);
		else
			rc = dump_regs_t4(argc, argv, regs.data);
	} else if (vers == 5) {
		if (revision == 0x3f)
			rc = dump_regs_t5vf(argc, argv, regs.data);
		else
			rc = dump_regs_t5(argc, argv, regs.data);
	} else if (vers == 6) {
		if (revision == 0x3f)
			rc = dump_regs_t6vf(argc, argv, regs.data);
		else
			rc = dump_regs_t6(argc, argv, regs.data);
	} else {
		warnx("%s (type %d, rev %d) is not a known card.",
		    nexus, vers, revision);
		return (ENOTSUP);
	}

	free(regs.data);
	return (rc);
}
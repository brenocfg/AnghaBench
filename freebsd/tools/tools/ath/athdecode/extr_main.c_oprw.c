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
struct dumpreg {char* name; char* bits; } ;
struct athregrec {int threadid; int reg; int val; scalar_t__ op; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AR_KEYTABLE (int) ; 
 int AR_KEYTABLE_0 ; 
 int AR_PHY_BASE ; 
 int AR_PHY_PCDAC_TX_POWER (int) ; 
 int AR_PHY_PCDAC_TX_POWER_0 ; 
 int AR_RATE_DURATION (int) ; 
 int AR_RATE_DURATION_0 ; 
 int PWR_TABLE_SIZE ; 
 struct dumpreg* findreg (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static void
oprw(FILE *fd, int recnum, struct athregrec *r)
{
	const struct dumpreg *dr;
	char buf[64];
	const char* bits;
	int i;

	fprintf(fd, "\n%05d: [%d] ", recnum, r->threadid);
	dr = findreg(r->reg);
	if (dr != NULL && dr->name != NULL) {
		snprintf(buf, sizeof (buf), "AR_%s (0x%x)", dr->name, r->reg);
		bits = dr->bits;
	} else if (AR_KEYTABLE(0) <= r->reg && r->reg < AR_KEYTABLE(128)) {
		snprintf(buf, sizeof (buf), "AR_KEYTABLE%u(%u) (0x%x)",
			((r->reg - AR_KEYTABLE_0) >> 2) & 7,
			(r->reg - AR_KEYTABLE_0) >> 5, r->reg);
		bits = NULL;
#if 0
	} else if (AR_PHY_PCDAC_TX_POWER(0) <= r->reg && r->reg < AR_PHY_PCDAC_TX_POWER(PWR_TABLE_SIZE/2)) {
		snprintf(buf, sizeof (buf), "AR_PHY_PCDAC_TX_POWER(%u) (0x%x)",
			(r->reg - AR_PHY_PCDAC_TX_POWER_0) >> 2, r->reg);
		bits = NULL;
#endif
	} else if (AR_RATE_DURATION(0) <= r->reg && r->reg < AR_RATE_DURATION(32)) {
		snprintf(buf, sizeof (buf), "AR_RATE_DURATION(0x%x) (0x%x)",
			(r->reg - AR_RATE_DURATION_0) >> 2, r->reg);
		bits = NULL;
	} else if (AR_PHY_BASE <= r->reg) {
		snprintf(buf, sizeof (buf), "AR_PHY(%u) (0x%x)",
			(r->reg - AR_PHY_BASE) >> 2, r->reg);
		bits = NULL;
	} else {
		snprintf(buf, sizeof (buf), "0x%x", r->reg);
		bits = NULL;
	}
	fprintf(fd, "%-30s %s 0x%x", buf, r->op ? "<=" : "=>", r->val);
	if (bits) {
		const char *p = bits;
		int tmp, n;

		for (tmp = 0, p++; *p;) {
			n = *p++;
			if (r->val & (1 << (n - 1))) {
				putc(tmp ? ',' : '<', fd);
				for (; (n = *p) > ' '; ++p)
					putc(n, fd);
				tmp = 1;
			} else
				for (; *p > ' '; ++p)
					continue;
		}
		if (tmp)
			putc('>', fd);
	}
}
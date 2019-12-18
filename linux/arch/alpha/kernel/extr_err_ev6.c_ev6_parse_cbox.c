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
typedef  int u64 ;

/* Variables and functions */
 int EV6__C_STAT__BC_PERR ; 
 int EV6__C_STAT__DC_PERR ; 
 int /*<<< orphan*/  EV6__C_STAT__DOUBLE ; 
 int EV6__C_STAT__ERRMASK ; 
 int /*<<< orphan*/  EV6__C_STAT__ISTREAM ; 
 int EV6__C_STAT__PROBE_BC_ERR0 ; 
 int EV6__C_STAT__PROBE_BC_ERR1 ; 
 int /*<<< orphan*/  EV6__C_STAT__SOURCE ; 
 int EV6__C_STAT__SOURCE_BCACHE ; 
 int EV6__C_STAT__SOURCE_MEMORY ; 
 int EV6__C_STS__DIRTY ; 
 int EV6__C_STS__PARITY ; 
 int EV6__C_STS__SHARED ; 
 int EV6__C_STS__VALID ; 
 int EXTRACT (int,int /*<<< orphan*/ ) ; 
 int MCHK_DISPOSITION_REPORT ; 
 int MCHK_DISPOSITION_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  err_print_prefix ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
ev6_parse_cbox(u64 c_addr, u64 c1_syn, u64 c2_syn, 
	       u64 c_stat, u64 c_sts, int print)
{
	static const char * const sourcename[] = {
		"UNKNOWN", "UNKNOWN", "UNKNOWN",
		"MEMORY", "BCACHE", "DCACHE",
		"BCACHE PROBE", "BCACHE PROBE"
	};
	static const char * const streamname[] = { "D", "I" };
	static const char * const bitsname[] = { "SINGLE", "DOUBLE" };
	int status = MCHK_DISPOSITION_REPORT;
	int source = -1, stream = -1, bits = -1;

#define EV6__C_STAT__BC_PERR		(0x01)
#define EV6__C_STAT__DC_PERR		(0x02)
#define EV6__C_STAT__DSTREAM_MEM_ERR	(0x03)
#define EV6__C_STAT__DSTREAM_BC_ERR	(0x04)
#define EV6__C_STAT__DSTREAM_DC_ERR	(0x05)
#define EV6__C_STAT__PROBE_BC_ERR0	(0x06)	/* both 6 and 7 indicate... */
#define EV6__C_STAT__PROBE_BC_ERR1	(0x07)	/* ...probe bc error.       */
#define EV6__C_STAT__ISTREAM_MEM_ERR	(0x0B)
#define EV6__C_STAT__ISTREAM_BC_ERR	(0x0C)
#define EV6__C_STAT__DSTREAM_MEM_DBL	(0x13)
#define EV6__C_STAT__DSTREAM_BC_DBL	(0x14)
#define EV6__C_STAT__ISTREAM_MEM_DBL	(0x1B)
#define EV6__C_STAT__ISTREAM_BC_DBL	(0x1C)
#define EV6__C_STAT__SOURCE_MEMORY	(0x03)
#define EV6__C_STAT__SOURCE_BCACHE	(0x04)
#define EV6__C_STAT__SOURCE__S		(0)
#define EV6__C_STAT__SOURCE__M 		(0x07)
#define EV6__C_STAT__ISTREAM__S		(3)
#define EV6__C_STAT__ISTREAM__M		(0x01)
#define EV6__C_STAT__DOUBLE__S		(4)
#define EV6__C_STAT__DOUBLE__M		(0x01)
#define EV6__C_STAT__ERRMASK		(0x1F)
#define EV6__C_STS__SHARED		(1 << 0)
#define EV6__C_STS__DIRTY		(1 << 1)
#define EV6__C_STS__VALID		(1 << 2)
#define EV6__C_STS__PARITY		(1 << 3)

	if (!(c_stat & EV6__C_STAT__ERRMASK))
		return MCHK_DISPOSITION_UNKNOWN_ERROR;

	if (!print)
		return status;

	source = EXTRACT(c_stat, EV6__C_STAT__SOURCE);
	stream = EXTRACT(c_stat, EV6__C_STAT__ISTREAM);
	bits = EXTRACT(c_stat, EV6__C_STAT__DOUBLE);

	if (c_stat & EV6__C_STAT__BC_PERR) {
		printk("%s    Bcache tag parity error\n", err_print_prefix);
		source = -1;
	}

	if (c_stat & EV6__C_STAT__DC_PERR) {
		printk("%s    Dcache tag parity error\n", err_print_prefix);
		source = -1;
	}

	if (c_stat == EV6__C_STAT__PROBE_BC_ERR0 ||
	    c_stat == EV6__C_STAT__PROBE_BC_ERR1) {
		printk("%s    Bcache single-bit error on a probe hit\n",
		       err_print_prefix);
		source = -1;
	}

	if (source != -1) 
		printk("%s    %s-STREAM %s-BIT ECC error from %s\n",
		       err_print_prefix,
		       streamname[stream], bitsname[bits], sourcename[source]);

	printk("%s    Address: 0x%016llx\n"
	         "    Syndrome[upper.lower]: %02llx.%02llx\n",
	       err_print_prefix,
	       c_addr,
	       c2_syn, c1_syn);

	if (source == EV6__C_STAT__SOURCE_MEMORY ||
	    source == EV6__C_STAT__SOURCE_BCACHE) 
		printk("%s    Block status: %s%s%s%s\n",
		       err_print_prefix,
		       (c_sts & EV6__C_STS__SHARED) ? "SHARED " : "",
		       (c_sts & EV6__C_STS__DIRTY)  ? "DIRTY "  : "",
		       (c_sts & EV6__C_STS__VALID)  ? "VALID "  : "",
		       (c_sts & EV6__C_STS__PARITY) ? "PARITY " : "");
		
	return status;
}
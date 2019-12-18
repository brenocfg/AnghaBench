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
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_TABLE_FADT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SIG_FADT ; 
 int /*<<< orphan*/  aml_disassemble (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dflag ; 
 int /*<<< orphan*/ * dsdt_from_fadt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dsdt_load_file (char*) ; 
 int /*<<< orphan*/  dsdt_save_file (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/ * sdt_from_rsdt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sdt_load_devmem () ; 
 int /*<<< orphan*/  sdt_print_all (int /*<<< orphan*/ *) ; 
 scalar_t__ tflag ; 
 int /*<<< orphan*/  usage (char*) ; 
 int vflag ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
main(int argc, char *argv[])
{
	ACPI_TABLE_HEADER *rsdt, *sdt;
	int	c;
	char	*progname;
	char	*dsdt_input_file, *dsdt_output_file;

	dsdt_input_file = dsdt_output_file = NULL;
	progname = argv[0];

	if (argc < 2)
		usage(progname);

	while ((c = getopt(argc, argv, "dhtvf:o:")) != -1) {
		switch (c) {
		case 'd':
			dflag = 1;
			break;
		case 't':
			tflag = 1;
			break;
		case 'v':
			vflag = 1;
			break;
		case 'f':
			dsdt_input_file = optarg;
			break;
		case 'o':
			dsdt_output_file = optarg;
			break;
		case 'h':
		default:
			usage(progname);
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	/* Get input either from file or /dev/mem */
	if (dsdt_input_file != NULL) {
		if (dflag == 0 && tflag == 0) {
			warnx("Need to specify -d or -t with DSDT input file");
			usage(progname);
		} else if (tflag != 0) {
			warnx("Can't use -t with DSDT input file");
			usage(progname);
		}
		if (vflag)
			warnx("loading DSDT file: %s", dsdt_input_file);
		rsdt = dsdt_load_file(dsdt_input_file);
	} else {
		if (vflag)
			warnx("loading RSD PTR from /dev/mem");
		rsdt = sdt_load_devmem();
	}

	/* Display misc. SDT tables (only available when using /dev/mem) */
	if (tflag) {
		if (vflag)
			warnx("printing various SDT tables");
		sdt_print_all(rsdt);
	}

	/* Translate RSDT to DSDT pointer */
	if (dsdt_input_file == NULL) {
		sdt = sdt_from_rsdt(rsdt, ACPI_SIG_FADT, NULL);
		sdt = dsdt_from_fadt((ACPI_TABLE_FADT *)sdt);
	} else {
		sdt = rsdt;
		rsdt = NULL;
	}

	/* Dump the DSDT and SSDTs to a file */
	if (dsdt_output_file != NULL) {
		if (vflag)
			warnx("saving DSDT file: %s", dsdt_output_file);
		dsdt_save_file(dsdt_output_file, rsdt, sdt);
	}

	/* Disassemble the DSDT into ASL */
	if (dflag) {
		if (vflag)
			warnx("disassembling DSDT, iasl messages follow");
		aml_disassemble(rsdt, sdt);
		if (vflag)
			warnx("iasl processing complete");
	}

	exit(0);
}
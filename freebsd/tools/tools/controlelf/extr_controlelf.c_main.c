#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* e_ident; int /*<<< orphan*/  e_phnum; } ;
typedef  TYPE_1__ GElf_Ehdr ;
typedef  scalar_t__ Elf_Kind ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 size_t EI_DATA ; 
 int /*<<< orphan*/  ELF_C_READ ; 
 scalar_t__ ELF_K_AR ; 
 scalar_t__ ELF_K_ELF ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 scalar_t__ EV_NONE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 scalar_t__ SUPPORTED_ENDIAN ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  edit_file_features (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 scalar_t__ elf_kind (int /*<<< orphan*/ *) ; 
 scalar_t__ elf_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  long_opts ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  print_features () ; 
 int /*<<< orphan*/  print_file_features (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
main(int argc, char **argv)
{
	GElf_Ehdr ehdr;
	Elf *elf;
	Elf_Kind kind;
	int ch, fd, editfeatures, retval;
	char *features;
	bool lflag;

	lflag = 0;
	editfeatures = 0;
	retval = 0;

	if (elf_version(EV_CURRENT) == EV_NONE)
		errx(EXIT_FAILURE, "elf_version error");

	while ((ch = getopt_long(argc, argv, "hle:", long_opts, NULL)) != -1) {
		switch (ch) {
		case 'l':
			print_features();
			lflag = true;
			break;
		case 'e':
			features = optarg;
			editfeatures = 1;
			break;
		case 'h':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	if (argc == 0) {
		if (lflag)
			exit(0);
		else {
			warnx("no file(s) specified");
			usage();
		}
	}

	while (argc) {
		elf = NULL;

		if ((fd = open(argv[0],
		    editfeatures ? O_RDWR : O_RDONLY, 0)) < 0) {
			warn("error opening file %s", argv[0]);
			retval = 1;
			goto fail;
		}

		if ((elf = elf_begin(fd, ELF_C_READ, NULL)) == NULL) {
			warnx("elf_begin failed: %s", elf_errmsg(-1));
			retval = 1;
			goto fail;
		}

		if ((kind = elf_kind(elf)) != ELF_K_ELF) {
			if (kind == ELF_K_AR)
				warnx("file '%s' is an archive", argv[0]);
			else
				warnx("file '%s' is not an ELF file", argv[0]);
			retval = 1;
			goto fail;
		}

		if (gelf_getehdr(elf, &ehdr) == NULL) {
			warnx("gelf_getehdr: %s", elf_errmsg(-1));
			retval = 1;
			goto fail;
		}
		/*
		 * XXX need to support cross-endian operation, but for now
		 * exit on error rather than misbehaving.
		 */
		if (ehdr.e_ident[EI_DATA] != SUPPORTED_ENDIAN) {
			warnx("file endianness must match host");
			retval = 1;
			goto fail;
		}

		if (!editfeatures) {
			if (!print_file_features(elf, ehdr.e_phnum, fd,
			    argv[0])) {
				retval = 1;
				goto fail;
			}
		} else if (!edit_file_features(elf, ehdr.e_phnum, fd,
		    features)) {
			retval = 1;
			goto fail;
		}
fail:
		if (elf != NULL)
			elf_end(elf);

		if (fd >= 0)
			close(fd);

		argc--;
		argv++;
	}

	return (retval);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct dos_partition {scalar_t__ dp_start; scalar_t__ dp_size; int dp_typ; int dp_flag; } ;
struct TYPE_2__ {struct dos_partition* parts; int /*<<< orphan*/ * bootinst; } ;

/* Variables and functions */
 int ACTIVE ; 
 int B_flag ; 
 int DOSPTYP_386BSD ; 
 int I_flag ; 
 int /*<<< orphan*/  MAX_SEC_SIZE ; 
 int NDOSPART ; 
 int a_flag ; 
 void* b_flag ; 
 int /*<<< orphan*/  change_active (int) ; 
 int /*<<< orphan*/  change_code () ; 
 int /*<<< orphan*/  change_part (int) ; 
 char* disk ; 
 int /*<<< orphan*/  disksecs ; 
 int /*<<< orphan*/  dos (struct dos_partition*) ; 
 int dos_cyls ; 
 int /*<<< orphan*/  dos_cylsecs ; 
 int dos_heads ; 
 int dos_sectors ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 void* f_flag ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 char* g_device_path (char*) ; 
 int /*<<< orphan*/  get_params_to_use () ; 
 char* get_rootdisk () ; 
 int getopt (int,char**,char*) ; 
 int i_flag ; 
 int /*<<< orphan*/  init_sector0 (int) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 TYPE_1__ mboot ; 
 scalar_t__ ok (char*) ; 
 scalar_t__ open_disk (int) ; 
 void* optarg ; 
 scalar_t__ optind ; 
 int print_config_flag ; 
 int /*<<< orphan*/  print_params () ; 
 int /*<<< orphan*/  print_s0 () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int q_flag ; 
 int /*<<< orphan*/  read_config (void*) ; 
 int read_disk (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ read_s0 () ; 
 int /*<<< orphan*/  reset_boot () ; 
 int rounddown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int s_flag ; 
 int secsize ; 
 int t_flag ; 
 int u_flag ; 
 int /*<<< orphan*/  usage () ; 
 int v_flag ; 
 int /*<<< orphan*/  write_s0 () ; 

int
main(int argc, char *argv[])
{
	int	c, i;
	int	partition = -1;
	struct	dos_partition *partp;

	while ((c = getopt(argc, argv, "BIab:f:ipqstuv1234")) != -1)
		switch (c) {
		case 'B':
			B_flag = 1;
			break;
		case 'I':
			I_flag = 1;
			break;
		case 'a':
			a_flag = 1;
			break;
		case 'b':
			b_flag = optarg;
			break;
		case 'f':
			f_flag = optarg;
			break;
		case 'i':
			i_flag = 1;
			break;
		case 'p':
			print_config_flag = 1;
			break;
		case 'q':
			q_flag = 1;
			break;
		case 's':
			s_flag = 1;
			break;
		case 't':
			t_flag = 1;
			break;
		case 'u':
			u_flag = 1;
			break;
		case 'v':
			v_flag = 1;
			break;
		case '1':
		case '2':
		case '3':
		case '4':
			partition = c - '0';
			break;
		default:
			usage();
		}
	if (f_flag || i_flag)
		u_flag = 1;
	if (t_flag)
		v_flag = 1;
	argc -= optind;
	argv += optind;

	if (argc == 0) {
		disk = get_rootdisk();
	} else {
		disk = g_device_path(argv[0]);
		if (disk == NULL)
			err(1, "unable to get correct path for %s", argv[0]);
	}
	if (open_disk(u_flag) < 0)
		err(1, "cannot open disk %s", disk);

	/* (abu)use mboot.bootinst to probe for the sector size */
	if ((mboot.bootinst = malloc(MAX_SEC_SIZE)) == NULL)
		err(1, "cannot allocate buffer to determine disk sector size");
	if (read_disk(0, mboot.bootinst) == -1)
		errx(1, "could not detect sector size");
	free(mboot.bootinst);
	mboot.bootinst = NULL;

	if (print_config_flag) {
		if (read_s0())
			err(1, "read_s0");

		printf("# %s\n", disk);
		printf("g c%d h%d s%d\n", dos_cyls, dos_heads, dos_sectors);

		for (i = 0; i < NDOSPART; i++) {
			partp = &mboot.parts[i];

			if (partp->dp_start == 0 && partp->dp_size == 0)
				continue;

			printf("p %d 0x%02x %lu %lu\n", i + 1, partp->dp_typ,
			    (u_long)partp->dp_start, (u_long)partp->dp_size);

			/* Fill flags for the partition. */
			if (partp->dp_flag & 0x80)
				printf("a %d\n", i + 1);
		}
		exit(0);
	}
	if (s_flag) {
		if (read_s0())
			err(1, "read_s0");
		printf("%s: %d cyl %d hd %d sec\n", disk, dos_cyls, dos_heads,
		    dos_sectors);
		printf("Part  %11s %11s Type Flags\n", "Start", "Size");
		for (i = 0; i < NDOSPART; i++) {
			partp = &mboot.parts[i];
			if (partp->dp_start == 0 && partp->dp_size == 0)
				continue;
			printf("%4d: %11lu %11lu 0x%02x 0x%02x\n", i + 1,
			    (u_long) partp->dp_start,
			    (u_long) partp->dp_size, partp->dp_typ,
			    partp->dp_flag);
		}
		exit(0);
	}

	printf("******* Working on device %s *******\n",disk);

	if (I_flag) {
		read_s0();
		reset_boot();
		partp = &mboot.parts[0];
		partp->dp_typ = DOSPTYP_386BSD;
		partp->dp_flag = ACTIVE;
		partp->dp_start = dos_sectors;
		partp->dp_size = rounddown(disksecs, dos_cylsecs) -
		    dos_sectors;
		dos(partp);
		if (v_flag)
			print_s0();
		if (!t_flag)
			write_s0();
		exit(0);
	}
	if (f_flag) {
	    if (read_s0() || i_flag)
		reset_boot();
	    if (!read_config(f_flag))
		exit(1);
	    if (v_flag)
		print_s0();
	    if (!t_flag)
		write_s0();
	} else {
	    if(u_flag)
		get_params_to_use();
	    else
		print_params();

	    if (read_s0())
		init_sector0(dos_sectors);

	    printf("Media sector size is %d\n", secsize);
	    printf("Warning: BIOS sector numbering starts with sector 1\n");
	    printf("Information from DOS bootblock is:\n");
	    if (partition == -1)
		for (i = 1; i <= NDOSPART; i++)
		    change_part(i);
	    else
		change_part(partition);

	    if (u_flag || a_flag)
		change_active(partition);

	    if (B_flag)
		change_code();

	    if (u_flag || a_flag || B_flag) {
		if (!t_flag) {
		    printf("\nWe haven't changed the partition table yet.  ");
		    printf("This is your last chance.\n");
		}
		print_s0();
		if (!t_flag) {
		    if (ok("Should we write new partition table?"))
			write_s0();
		} else {
		    printf("\n-t flag specified -- partition table not written.\n");
		}
	    }
	}

	exit(0);
}
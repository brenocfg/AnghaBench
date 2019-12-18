#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
typedef  scalar_t__ uint16_t ;
struct stat {int st_size; } ;
struct i386_devdesc {int dummy; } ;
struct TYPE_4__ {int (* arch_readin ) (int,int,int) ;} ;
struct TYPE_3__ {int src; int dest; int size; } ;

/* Variables and functions */
 int CMD_ERROR ; 
 scalar_t__ DOSMAGIC ; 
 int DOSMAGICOFFSET ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ PTOV (int) ; 
 int SECTOR_SIZE ; 
 int /*<<< orphan*/  VE_MUST ; 
 int /*<<< orphan*/  __exec (void*) ; 
 TYPE_2__ archsw ; 
 int /*<<< orphan*/  bd_unit2bios (struct i386_devdesc*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  command_errbuf ; 
 char* command_errmsg ; 
 int /*<<< orphan*/  dev_cleanup () ; 
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/  i386_copyin (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i386_getdev (void**,char*,int /*<<< orphan*/ *) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  relocater ; 
 TYPE_1__* relocater_data ; 
 int /*<<< orphan*/  relocater_size ; 
 scalar_t__ relocator_a20_enabled ; 
 scalar_t__ relocator_cs ; 
 scalar_t__ relocator_ds ; 
 int /*<<< orphan*/  relocator_edx ; 
 scalar_t__ relocator_es ; 
 int /*<<< orphan*/  relocator_esi ; 
 scalar_t__ relocator_fs ; 
 scalar_t__ relocator_gs ; 
 int relocator_ip ; 
 int relocator_sp ; 
 scalar_t__ relocator_ss ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int stub1 (int,int,int) ; 
 scalar_t__ verify_file (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
command_chain(int argc, char *argv[])
{
	int fd, len, size = SECTOR_SIZE;
	struct stat st;
	vm_offset_t mem = 0x100000;
	struct i386_devdesc *rootdev;

	if (argc == 1) {
		command_errmsg = "no device or file name specified";
		return (CMD_ERROR);
	}
	if (argc != 2) {
		command_errmsg = "invalid trailing arguments";
		return (CMD_ERROR);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		command_errmsg = "open failed";
		return (CMD_ERROR);
	}

#ifdef LOADER_VERIEXEC
	if (verify_file(fd, argv[1], 0, VE_MUST) < 0) {
		sprintf(command_errbuf, "can't verify: %s", argv[1]);
		close(fd);
		return (CMD_ERROR);
	}
#endif

	len = strlen(argv[1]);
	if (argv[1][len-1] != ':') {
		if (fstat(fd, &st) == -1) {
			command_errmsg = "stat failed";
			close(fd);
			return (CMD_ERROR);
		}
		size = st.st_size;
	} else if (strncmp(argv[1], "disk", 4) != 0) {
		command_errmsg = "can only use disk device";
		close(fd);
		return (CMD_ERROR);
	}

	i386_getdev((void **)(&rootdev), argv[1], NULL);
	if (rootdev == NULL) {
		command_errmsg = "can't determine root device";
		close(fd);
		return (CMD_ERROR);
	}

	if (archsw.arch_readin(fd, mem, size) != size) {
		command_errmsg = "failed to read disk";
		close(fd);
		return (CMD_ERROR);
	}
	close(fd);

	if (argv[1][len-1] == ':' &&
	    *((uint16_t *)PTOV(mem + DOSMAGICOFFSET)) != DOSMAGIC) {
		command_errmsg = "wrong magic";
		return (CMD_ERROR);
	}

	relocater_data[0].src = mem;
	relocater_data[0].dest = 0x7C00;
	relocater_data[0].size = size;

	relocator_edx = bd_unit2bios(rootdev);
	relocator_esi = relocater_size;
	relocator_ds = 0;
	relocator_es = 0;
	relocator_fs = 0;
	relocator_gs = 0;
	relocator_ss = 0;
	relocator_cs = 0;
	relocator_sp = 0x7C00;
	relocator_ip = 0x7C00;
	relocator_a20_enabled = 0;

	i386_copyin(relocater, 0x600, relocater_size);

	dev_cleanup();

	__exec((void *)0x600);

	panic("exec returned");
	return (CMD_ERROR);		/* not reached */
}
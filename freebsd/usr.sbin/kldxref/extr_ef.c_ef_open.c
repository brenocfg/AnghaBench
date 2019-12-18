#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct elf_file {int /*<<< orphan*/ * ef_ops; TYPE_1__* ef_ef; } ;
typedef  TYPE_1__* elf_file_t ;
struct TYPE_14__ {scalar_t__* e_ident; scalar_t__ e_version; scalar_t__ e_machine; int e_phentsize; int e_phnum; scalar_t__ e_type; int /*<<< orphan*/  e_phoff; } ;
struct TYPE_13__ {int p_type; int p_filesz; int /*<<< orphan*/  p_offset; } ;
struct TYPE_12__ {int ef_verbose; int ef_fd; int ef_nsegs; int /*<<< orphan*/  ef_type; int /*<<< orphan*/  ef_dyn; TYPE_2__** ef_segs; TYPE_2__* ef_ph; int /*<<< orphan*/  ef_hdr; struct elf_file* ef_efile; int /*<<< orphan*/  ef_name; } ;
typedef  TYPE_2__ Elf_Phdr ;
typedef  TYPE_3__ Elf_Ehdr ;

/* Variables and functions */
 int EFTYPE ; 
 int /*<<< orphan*/  EFT_KERNEL ; 
 int /*<<< orphan*/  EFT_KLD ; 
 int EINVAL ; 
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 size_t EI_VERSION ; 
 scalar_t__ ELF_TARG_CLASS ; 
 scalar_t__ ELF_TARG_DATA ; 
 scalar_t__ ELF_TARG_MACH ; 
 scalar_t__ ET_DYN ; 
 scalar_t__ ET_EXEC ; 
 scalar_t__ EV_CURRENT ; 
 int /*<<< orphan*/  IS_ELF (TYPE_3__) ; 
 int MAXSEGS ; 
 int /*<<< orphan*/  O_RDONLY ; 
#define  PT_DYNAMIC 130 
#define  PT_LOAD 129 
#define  PT_PHDR 128 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ef_close (TYPE_1__*) ; 
 int /*<<< orphan*/  ef_file_ops ; 
 int ef_parse_dynamic (TYPE_1__*) ; 
 int /*<<< orphan*/  ef_print_phdr (TYPE_2__*) ; 
 scalar_t__ ef_read_entry (TYPE_1__*,int /*<<< orphan*/ ,int,void**) ; 
 int errno ; 
 TYPE_1__* malloc (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int read (int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

int
ef_open(const char *filename, struct elf_file *efile, int verbose)
{
	elf_file_t ef;
	Elf_Ehdr *hdr;
	int fd;
	int error;
	int phlen, res;
	int nsegs;
	Elf_Phdr *phdr, *phdyn, *phlimit;

	if (filename == NULL)
		return (EINVAL);
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (errno);

	ef = malloc(sizeof(*ef));
	if (ef == NULL) {
		close(fd);
		return (errno);
	}

	efile->ef_ef = ef;
	efile->ef_ops = &ef_file_ops;

	bzero(ef, sizeof(*ef));
	ef->ef_verbose = verbose;
	ef->ef_fd = fd;
	ef->ef_name = strdup(filename);
	ef->ef_efile = efile;
	hdr = (Elf_Ehdr *)&ef->ef_hdr;
	do {
		res = read(fd, hdr, sizeof(*hdr));
		error = EFTYPE;
		if (res != sizeof(*hdr))
			break;
		if (!IS_ELF(*hdr))
			break;
		if (hdr->e_ident[EI_CLASS] != ELF_TARG_CLASS ||
		    hdr->e_ident[EI_DATA] != ELF_TARG_DATA ||
		    hdr->e_ident[EI_VERSION] != EV_CURRENT ||
		    hdr->e_version != EV_CURRENT ||
		    hdr->e_machine != ELF_TARG_MACH ||
		    hdr->e_phentsize != sizeof(Elf_Phdr))
			break;
		phlen = hdr->e_phnum * sizeof(Elf_Phdr);
		if (ef_read_entry(ef, hdr->e_phoff, phlen,
		    (void **)&ef->ef_ph) != 0)
			break;
		phdr = ef->ef_ph;
		phlimit = phdr + hdr->e_phnum;
		nsegs = 0;
		phdyn = NULL;
		while (phdr < phlimit) {
			if (verbose > 1)
				ef_print_phdr(phdr);
			switch (phdr->p_type) {
			case PT_LOAD:
				if (nsegs < MAXSEGS)
					ef->ef_segs[nsegs] = phdr;
				nsegs++;
				break;
			case PT_PHDR:
				break;
			case PT_DYNAMIC:
				phdyn = phdr;
				break;
			}
			phdr++;
		}
		if (verbose > 1)
			printf("\n");
		if (phdyn == NULL) {
			warnx("Skipping %s: not dynamically-linked",
			    filename);
			break;
		} else if (nsegs > MAXSEGS) {
			warnx("%s: too many segments", filename);
			break;
		}
		ef->ef_nsegs = nsegs;
		if (ef_read_entry(ef, phdyn->p_offset,
			phdyn->p_filesz, (void **)&ef->ef_dyn) != 0) {
			printf("ef_read_entry failed\n");
			break;
		}
		error = ef_parse_dynamic(ef);
		if (error != 0)
			break;
		if (hdr->e_type == ET_DYN) {
			ef->ef_type = EFT_KLD;
			error = 0;
		} else if (hdr->e_type == ET_EXEC) {
			ef->ef_type = EFT_KERNEL;
			error = 0;
		} else
			break;
	} while(0);
	if (error != 0)
		ef_close(ef);
	return (error);
}
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
struct stat {int st_mode; int /*<<< orphan*/  st_size; } ;
struct section_dispatch_table {int sdt_rel; int sdt_hash; int sdt_nzlist; int sdt_strings; } ;
struct relocation_info {int dummy; } ;
struct nzlist {int dummy; } ;
struct nlist {int dummy; } ;
struct exec {int a_syms; scalar_t__ a_entry; int a_trsize; int a_drsize; scalar_t__ a_bss; scalar_t__ a_data; scalar_t__ a_text; scalar_t__ a_midmag; } ;
struct TYPE_2__ {scalar_t__ d_sdt; } ;
struct _dynamic {long d_version; TYPE_1__ d_un; } ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  Elf32_Ehdr ;

/* Variables and functions */
 int EX_DYNAMIC ; 
 scalar_t__ IS_ELF (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 scalar_t__ N_BADMAG (struct exec const) ; 
 scalar_t__ N_DATADDR (struct exec const) ; 
 int N_DATOFF (struct exec const) ; 
 int N_GETFLAG (struct exec const) ; 
 scalar_t__ N_GETMAGIC (struct exec const) ; 
 scalar_t__ N_GETMAGIC_NET (struct exec const) ; 
 int N_RELOFF (struct exec const) ; 
 int N_STROFF (struct exec const) ; 
 int N_SYMOFF (struct exec const) ; 
 scalar_t__ N_TXTADDR (struct exec const) ; 
 int N_TXTOFF (struct exec const) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PROT_READ ; 
 int S_IFMT ; 
 int S_IFREG ; 
 scalar_t__ align_struct (void*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 void* data_addr ; 
 void* data_base ; 
 int /*<<< orphan*/  dump_rels (char*,struct relocation_info const*,int,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  dump_rtsyms () ; 
 int /*<<< orphan*/  dump_segs () ; 
 int /*<<< orphan*/  dump_sods () ; 
 int /*<<< orphan*/  dump_syms () ; 
 struct _dynamic const* dyn ; 
 int /*<<< orphan*/  error_count ; 
 struct exec const* ex ; 
 void* file_base ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (scalar_t__,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long origin ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 struct relocation_info const* rel_base ; 
 int rel_count ; 
 struct relocation_info const* rtrel_base ; 
 int rtrel_count ; 
 void* rtstr_base ; 
 struct nzlist const* rtsym_base ; 
 int rtsym_count ; 
 int /*<<< orphan*/  rtsym_name ; 
 unsigned char* rtsym_used ; 
 struct section_dispatch_table const* sdt ; 
 int stat (char const*,struct stat*) ; 
 void* str_base ; 
 struct nlist const* sym_base ; 
 int sym_count ; 
 int /*<<< orphan*/  sym_name ; 
 unsigned char* sym_used ; 
 void* text_addr ; 
 void* text_base ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

void
dump_file(const char *fname)
{
    int fd;
    struct stat sb;
    caddr_t objbase;

    if (stat(fname, &sb) == -1) {
	warnx("cannot stat \"%s\"", fname);
	++error_count;
	return;
    }

    if ((sb.st_mode & S_IFMT) != S_IFREG) {
	warnx("\"%s\" is not a regular file", fname);
	++error_count;
	return;
    }

    if ((fd = open(fname, O_RDONLY, 0)) == -1) {
	warnx("cannot open \"%s\"", fname);
	++error_count;
	return;
    }

    objbase = mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (objbase == (caddr_t) -1) {
	warnx("cannot mmap \"%s\"", fname);
	++error_count;
	close(fd);
	return;
    }

    close(fd);

    file_base = (const char *) objbase;	/* Makes address arithmetic easier */

    if (IS_ELF(*(const Elf32_Ehdr*) align_struct(file_base))) {
	warnx("%s: this is an ELF program; use readelf to examine", fname);
	++error_count;
	munmap(objbase, sb.st_size);
	return;
    }

    ex = (const struct exec *) align_struct(file_base);

    printf("%s: a_midmag = 0x%lx\n", fname, (long)ex->a_midmag);
    printf("  magic = 0x%lx = 0%lo, netmagic = 0x%lx = 0%lo\n",
	(long)N_GETMAGIC(*ex), (long)N_GETMAGIC(*ex),
	(long)N_GETMAGIC_NET(*ex), (long)N_GETMAGIC_NET(*ex));

    if (N_BADMAG(*ex)) {
	warnx("%s: bad magic number", fname);
	++error_count;
	munmap(objbase, sb.st_size);
	return;
    }

    printf("  a_text   = 0x%lx\n", (long)ex->a_text);
    printf("  a_data   = 0x%lx\n", (long)ex->a_data);
    printf("  a_bss    = 0x%lx\n", (long)ex->a_bss);
    printf("  a_syms   = 0x%lx\n", (long)ex->a_syms);
    printf("  a_entry  = 0x%lx\n", (long)ex->a_entry);
    printf("  a_trsize = 0x%lx\n", (long)ex->a_trsize);
    printf("  a_drsize = 0x%lx\n", (long)ex->a_drsize);

    text_base = file_base + N_TXTOFF(*ex);
    data_base = file_base + N_DATOFF(*ex);
    rel_base = (const struct relocation_info *)
	align_struct(file_base + N_RELOFF(*ex));
    sym_base = (const struct nlist *) align_struct(file_base + N_SYMOFF(*ex));
    str_base = file_base + N_STROFF(*ex);

    rel_count = (ex->a_trsize + ex->a_drsize) / sizeof rel_base[0];
    assert(rel_count * sizeof rel_base[0] == ex->a_trsize + ex->a_drsize);
    sym_count = ex->a_syms / sizeof sym_base[0];
    assert(sym_count * sizeof sym_base[0] == ex->a_syms);

    if (sym_count != 0) {
	sym_used = (unsigned char *) calloc(sym_count, sizeof(unsigned char));
	assert(sym_used != NULL);
    }

    printf("  Entry = 0x%lx\n", (long)ex->a_entry);
    printf("  Text offset = %x, address = %lx\n", N_TXTOFF(*ex),
	(long)N_TXTADDR(*ex));
    printf("  Data offset = %lx, address = %lx\n", (long)N_DATOFF(*ex),
	(long)N_DATADDR(*ex));

    /*
     * In an executable program file, everything is relocated relative to
     * the assumed run-time load address, i.e., N_TXTADDR(*ex), i.e., 0x1000.
     *
     * In a shared library file, everything is relocated relative to the
     * start of the file, i.e., N_TXTOFF(*ex), i.e., 0.
     *
     * The way to tell the difference is by looking at ex->a_entry.   If it
     * is >= 0x1000, then we have an executable program.  Otherwise, we
     * have a shared library.
     *
     * When a program is executed, the entire file is mapped into memory,
     * including the a.out header and so forth.  But it is not mapped at
     * address 0; rather it is mapped at address 0x1000.  The first page
     * of the user's address space is left unmapped in order to catch null
     * pointer dereferences.
     *
     * In this program, when we map in an executable program, we have to
     * simulate the empty page by decrementing our assumed base address by
     * a pagesize.
     */

    text_addr = text_base;
    data_addr = data_base;
    origin = 0;

    if (ex->a_entry >= PAGE_SIZE) {	/* Executable, not a shared library */
	/*
	 * The fields in the object have already been relocated on the
	 * assumption that the object will be loaded at N_TXTADDR(*ex).
	 * We have to compensate for that.
	 */
	text_addr -= PAGE_SIZE;
	data_addr -= PAGE_SIZE;
	origin = PAGE_SIZE;
	printf("  Program, origin = %lx\n", origin);
    } else if (N_GETFLAG(*ex) & EX_DYNAMIC)
	printf("  Shared library, origin = %lx\n", origin);
    else
	printf("  Object file, origin = %lx\n", origin);

    if (N_GETFLAG(*ex) & EX_DYNAMIC) {
	dyn = (const struct _dynamic *) align_struct(data_base);
	printf("  Dynamic version = %d\n", dyn->d_version);

	sdt = (const struct section_dispatch_table *)
	    align_struct(text_addr + (unsigned long) dyn->d_un.d_sdt);

	rtrel_base = (const struct relocation_info *)
	    align_struct(text_addr + sdt->sdt_rel);
	rtrel_count = (sdt->sdt_hash - sdt->sdt_rel) / sizeof rtrel_base[0];
	assert(rtrel_count * sizeof rtrel_base[0] ==
	    (size_t)(sdt->sdt_hash - sdt->sdt_rel));

	rtsym_base = (const struct nzlist *)
	    align_struct(text_addr + sdt->sdt_nzlist);
	rtsym_count = (sdt->sdt_strings - sdt->sdt_nzlist) /
	    sizeof rtsym_base[0];
	assert(rtsym_count * sizeof rtsym_base[0] ==
	    (size_t)(sdt->sdt_strings - sdt->sdt_nzlist));

	if (rtsym_count != 0) {
	    rtsym_used = (unsigned char *) calloc(rtsym_count,
		sizeof(unsigned char));
	    assert(rtsym_used != NULL);
	}

	rtstr_base = text_addr + sdt->sdt_strings;
    }

    dump_segs();
    dump_sods();
    dump_rels("Relocations", rel_base, rel_count, sym_name, sym_used);
    dump_syms();

    dump_rels("Run-time relocations", rtrel_base, rtrel_count, rtsym_name,
	rtsym_used);
    dump_rtsyms();

    if (rtsym_used != NULL) {
	free(rtsym_used);
	rtsym_used = NULL;
    }
    if (sym_used != NULL) {
	free(sym_used);
	sym_used = NULL;
    }
    munmap(objbase, sb.st_size);
}
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
typedef  int /*<<< orphan*/  vm_map_entry_t ;
typedef  int uintmax_t ;
struct sseg_closure {int count; scalar_t__ size; } ;
struct sbuf {int dummy; } ;
struct ptrace_io_desc {char* piod_addr; int piod_len; int /*<<< orphan*/ * piod_offs; int /*<<< orphan*/  piod_op; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/ * caddr_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int p_filesz; scalar_t__ p_vaddr; } ;
typedef  int /*<<< orphan*/  Elf_Shdr ;
typedef  TYPE_1__ Elf_Phdr ;
typedef  int /*<<< orphan*/  Elf_Ehdr ;

/* Variables and functions */
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  PIOD_READ_D ; 
 int PN_XNUM ; 
 int /*<<< orphan*/  PT_ATTACH ; 
 int /*<<< orphan*/  PT_IO ; 
 scalar_t__ atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb_size_segment ; 
 int /*<<< orphan*/  each_dumpable_segment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sseg_closure*) ; 
 int /*<<< orphan*/  elf_detach ; 
 int /*<<< orphan*/  elf_puthdr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,size_t,size_t,int) ; 
 int /*<<< orphan*/  elf_putnotes (int /*<<< orphan*/ ,struct sbuf*,size_t*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  freemap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_pid ; 
 int /*<<< orphan*/  g_status ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readmap (int /*<<< orphan*/ ) ; 
 void* sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_end_section (struct sbuf*,int,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ sbuf_finish (struct sbuf*) ; 
 size_t sbuf_len (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  sbuf_putc (struct sbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_start_section (struct sbuf*,int*) ; 
 int waitpid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int write (int,char*,size_t) ; 

__attribute__((used)) static void
elf_coredump(int efd, int fd, pid_t pid)
{
	vm_map_entry_t map;
	struct sseg_closure seginfo;
	struct sbuf *sb;
	void *hdr;
	size_t hdrsize, notesz, segoff;
	ssize_t n, old_len;
	Elf_Phdr *php;
	int i;

	/* Attach to process to dump. */
	g_pid = pid;
	if (atexit(elf_detach) != 0)
		err(1, "atexit");
	errno = 0;
	ptrace(PT_ATTACH, pid, NULL, 0);
	if (errno)
		err(1, "PT_ATTACH");
	if (waitpid(pid, &g_status, 0) == -1)
		err(1, "waitpid");

	/* Get the program's memory map. */
	map = readmap(pid);

	/* Size the program segments. */
	seginfo.count = 0;
	seginfo.size = 0;
	each_dumpable_segment(map, cb_size_segment, &seginfo);

	/*
	 * Build the header and the notes using sbuf and write to the file.
	 */
	sb = sbuf_new_auto();
	hdrsize = sizeof(Elf_Ehdr) + sizeof(Elf_Phdr) * (1 + seginfo.count);
	if (seginfo.count + 1 >= PN_XNUM)
		hdrsize += sizeof(Elf_Shdr);
	/* Start header + notes section. */
	sbuf_start_section(sb, NULL);
	/* Make empty header subsection. */
	sbuf_start_section(sb, &old_len);
	sbuf_putc(sb, 0);
	sbuf_end_section(sb, old_len, hdrsize, 0);
	/* Put notes. */
	elf_putnotes(pid, sb, &notesz);
	/* Align up to a page boundary for the program segments. */
	sbuf_end_section(sb, -1, PAGE_SIZE, 0);
	if (sbuf_finish(sb) != 0)
		err(1, "sbuf_finish");
	hdr = sbuf_data(sb);
	segoff = sbuf_len(sb);
	/* Fill in the header. */
	elf_puthdr(efd, pid, map, hdr, hdrsize, notesz, segoff, seginfo.count);

	n = write(fd, hdr, segoff);
	if (n == -1)
		err(1, "write");
	if (n < segoff)
              errx(1, "short write");

	/* Write the contents of all of the writable segments. */
	php = (Elf_Phdr *)((char *)hdr + sizeof(Elf_Ehdr)) + 1;
	for (i = 0;  i < seginfo.count;  i++) {
		struct ptrace_io_desc iorequest;
		uintmax_t nleft = php->p_filesz;

		iorequest.piod_op = PIOD_READ_D;
		iorequest.piod_offs = (caddr_t)(uintptr_t)php->p_vaddr;
		while (nleft > 0) {
			char buf[8*1024];
			size_t nwant;
			ssize_t ngot;

			if (nleft > sizeof(buf))
				nwant = sizeof buf;
			else
				nwant = nleft;
			iorequest.piod_addr = buf;
			iorequest.piod_len = nwant;
			ptrace(PT_IO, pid, (caddr_t)&iorequest, 0);
			ngot = iorequest.piod_len;
			if ((size_t)ngot < nwant)
				errx(1, "short read wanted %zu, got %zd",
				    nwant, ngot);
			ngot = write(fd, buf, nwant);
			if (ngot == -1)
				err(1, "write of segment %d failed", i);
			if ((size_t)ngot != nwant)
				errx(1, "short write");
			nleft -= nwant;
			iorequest.piod_offs += ngot;
		}
		php++;
	}
	sbuf_delete(sb);
	freemap(map);
}
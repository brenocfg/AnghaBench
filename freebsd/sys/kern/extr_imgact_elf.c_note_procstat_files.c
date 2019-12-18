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
typedef  int /*<<< orphan*/  structsize ;
struct sbuf {scalar_t__ s_error; } ;
struct proc {int dummy; } ;
struct kinfo_file {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KERN_FILEDESC_PACK_KINFO ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 scalar_t__ coredump_pack_fileinfo ; 
 int /*<<< orphan*/  kern_proc_filedesc_out (struct proc*,struct sbuf*,size_t,int) ; 
 int /*<<< orphan*/  sbuf_bcat (struct sbuf*,int*,int) ; 
 int /*<<< orphan*/  sbuf_count_drain ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 size_t sbuf_end_section (struct sbuf*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_putc (struct sbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_set_drain (struct sbuf*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  sbuf_start_section (struct sbuf*,size_t*) ; 

__attribute__((used)) static void
note_procstat_files(void *arg, struct sbuf *sb, size_t *sizep)
{
	struct proc *p;
	size_t size, sect_sz, i;
	ssize_t start_len, sect_len;
	int structsize, filedesc_flags;

	if (coredump_pack_fileinfo)
		filedesc_flags = KERN_FILEDESC_PACK_KINFO;
	else
		filedesc_flags = 0;

	p = (struct proc *)arg;
	structsize = sizeof(struct kinfo_file);
	if (sb == NULL) {
		size = 0;
		sb = sbuf_new(NULL, NULL, 128, SBUF_FIXEDLEN);
		sbuf_set_drain(sb, sbuf_count_drain, &size);
		sbuf_bcat(sb, &structsize, sizeof(structsize));
		PROC_LOCK(p);
		kern_proc_filedesc_out(p, sb, -1, filedesc_flags);
		sbuf_finish(sb);
		sbuf_delete(sb);
		*sizep = size;
	} else {
		sbuf_start_section(sb, &start_len);

		sbuf_bcat(sb, &structsize, sizeof(structsize));
		PROC_LOCK(p);
		kern_proc_filedesc_out(p, sb, *sizep - sizeof(structsize),
		    filedesc_flags);

		sect_len = sbuf_end_section(sb, start_len, 0, 0);
		if (sect_len < 0)
			return;
		sect_sz = sect_len;

		KASSERT(sect_sz <= *sizep,
		    ("kern_proc_filedesc_out did not respect maxlen; "
		     "requested %zu, got %zu", *sizep - sizeof(structsize),
		     sect_sz - sizeof(structsize)));

		for (i = 0; i < *sizep - sect_sz && sb->s_error == 0; i++)
			sbuf_putc(sb, 0);
	}
}
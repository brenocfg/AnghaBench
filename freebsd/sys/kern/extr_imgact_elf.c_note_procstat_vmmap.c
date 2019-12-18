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
struct sbuf {int dummy; } ;
struct proc {int dummy; } ;
struct kinfo_vmentry {int dummy; } ;

/* Variables and functions */
 int KERN_VMMAP_PACK_KINFO ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 scalar_t__ coredump_pack_vmmapinfo ; 
 int /*<<< orphan*/  kern_proc_vmmap_out (struct proc*,struct sbuf*,size_t,int) ; 
 int /*<<< orphan*/  sbuf_bcat (struct sbuf*,int*,int) ; 
 int /*<<< orphan*/  sbuf_count_drain ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_set_drain (struct sbuf*,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static void
note_procstat_vmmap(void *arg, struct sbuf *sb, size_t *sizep)
{
	struct proc *p;
	size_t size;
	int structsize, vmmap_flags;

	if (coredump_pack_vmmapinfo)
		vmmap_flags = KERN_VMMAP_PACK_KINFO;
	else
		vmmap_flags = 0;

	p = (struct proc *)arg;
	structsize = sizeof(struct kinfo_vmentry);
	if (sb == NULL) {
		size = 0;
		sb = sbuf_new(NULL, NULL, 128, SBUF_FIXEDLEN);
		sbuf_set_drain(sb, sbuf_count_drain, &size);
		sbuf_bcat(sb, &structsize, sizeof(structsize));
		PROC_LOCK(p);
		kern_proc_vmmap_out(p, sb, -1, vmmap_flags);
		sbuf_finish(sb);
		sbuf_delete(sb);
		*sizep = size;
	} else {
		sbuf_bcat(sb, &structsize, sizeof(structsize));
		PROC_LOCK(p);
		kern_proc_vmmap_out(p, sb, *sizep - sizeof(structsize),
		    vmmap_flags);
	}
}
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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct preloaded_file {struct file_metadata* f_metadata; int /*<<< orphan*/  f_size; int /*<<< orphan*/  f_addr; scalar_t__ f_args; int /*<<< orphan*/  f_type; int /*<<< orphan*/  f_name; struct preloaded_file* f_next; } ;
struct file_metadata {int md_type; struct file_metadata* md_next; } ;

/* Variables and functions */
 int MODINFOMD_NOCOPY ; 
 int /*<<< orphan*/  MOD_ADDR (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MOD_ARGS (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  MOD_END (scalar_t__,int) ; 
 int /*<<< orphan*/  MOD_METADATA (scalar_t__,struct file_metadata*,int) ; 
 int /*<<< orphan*/  MOD_NAME (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MOD_SIZE (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MOD_TYPE (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ __elfN (int /*<<< orphan*/ ) ; 
 struct preloaded_file* file_findfile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  relocation_offset ; 

__attribute__((used)) static vm_offset_t
bi_copymodules(vm_offset_t addr)
{
	struct preloaded_file *fp;
	struct file_metadata *md;
	int c;
	uint64_t v;

	c = addr != 0;
	/* Start with the first module on the list, should be the kernel. */
	for (fp = file_findfile(NULL, NULL); fp != NULL; fp = fp->f_next) {
		MOD_NAME(addr, fp->f_name, c); /* This must come first. */
		MOD_TYPE(addr, fp->f_type, c);
		if (fp->f_args)
			MOD_ARGS(addr, fp->f_args, c);
		v = fp->f_addr;
#if defined(__arm__)
		v -= __elfN(relocation_offset);
#endif
		MOD_ADDR(addr, v, c);
		v = fp->f_size;
		MOD_SIZE(addr, v, c);
		for (md = fp->f_metadata; md != NULL; md = md->md_next)
			if (!(md->md_type & MODINFOMD_NOCOPY))
				MOD_METADATA(addr, md, c);
	}
	MOD_END(addr, c);
	return(addr);
}
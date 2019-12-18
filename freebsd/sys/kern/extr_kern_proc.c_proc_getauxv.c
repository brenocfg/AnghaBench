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
struct thread {int dummy; } ;
struct sbuf {int dummy; } ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  Elf_Auxinfo ;
typedef  int /*<<< orphan*/  Elf32_Auxinfo ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  PROC_AUX ; 
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ SV_PROC_FLAG (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char**,int /*<<< orphan*/ ) ; 
 int get_proc_vector (struct thread*,struct proc*,char***,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ sbuf_bcat (struct sbuf*,char**,size_t) ; 

int
proc_getauxv(struct thread *td, struct proc *p, struct sbuf *sb)
{
	size_t vsize, size;
	char **auxv;
	int error;

	error = get_proc_vector(td, p, &auxv, &vsize, PROC_AUX);
	if (error == 0) {
#ifdef COMPAT_FREEBSD32
		if (SV_PROC_FLAG(p, SV_ILP32) != 0)
			size = vsize * sizeof(Elf32_Auxinfo);
		else
#endif
			size = vsize * sizeof(Elf_Auxinfo);
		if (sbuf_bcat(sb, auxv, size) != 0)
			error = ENOMEM;
		free(auxv, M_TEMP);
	}
	return (error);
}
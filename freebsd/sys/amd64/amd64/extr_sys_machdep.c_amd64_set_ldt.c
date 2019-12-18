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
typedef  scalar_t__ uint64_t ;
typedef  size_t u_int ;
struct user_segment_descriptor {int sd_type; scalar_t__ sd_p; scalar_t__ sd_dpl; } ;
struct thread {size_t* td_retval; struct proc* td_proc; int /*<<< orphan*/  td_pcb; } ;
struct proc_ldt {scalar_t__ ldt_base; } ;
struct mdproc {struct proc_ldt* md_ldt; } ;
struct proc {struct mdproc p_md; } ;
struct i386_ldt_args {int start; int num; scalar_t__ descs; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 size_t LDT_AUTO_ALLOC ; 
 int /*<<< orphan*/  PCB_FULL_IRET ; 
#define  SDT_MEME 159 
#define  SDT_MEMEA 158 
#define  SDT_MEMEAC 157 
#define  SDT_MEMEC 156 
#define  SDT_MEMER 155 
#define  SDT_MEMERA 154 
#define  SDT_MEMERAC 153 
#define  SDT_MEMERC 152 
#define  SDT_MEMRO 151 
#define  SDT_MEMROA 150 
#define  SDT_MEMROD 149 
#define  SDT_MEMRODA 148 
#define  SDT_MEMRW 147 
#define  SDT_MEMRWA 146 
#define  SDT_MEMRWD 145 
#define  SDT_MEMRWDA 144 
#define  SDT_SYS286BSY 143 
#define  SDT_SYS286CGT 142 
#define  SDT_SYS286IGT 141 
#define  SDT_SYS286TGT 140 
#define  SDT_SYS286TSS 139 
#define  SDT_SYSBSY 138 
#define  SDT_SYSCGT 137 
#define  SDT_SYSIGT 136 
#define  SDT_SYSLDT 135 
#define  SDT_SYSNULL 134 
#define  SDT_SYSNULL2 133 
#define  SDT_SYSNULL3 132 
#define  SDT_SYSNULL4 131 
#define  SDT_SYSTASKGT 130 
#define  SDT_SYSTGT 129 
#define  SDT_SYSTSS 128 
 scalar_t__ SEL_UPL ; 
 int amd64_set_ldt_data (struct thread*,size_t,int,struct user_segment_descriptor*) ; 
 int /*<<< orphan*/  dt_lock ; 
 size_t max_ldt_segment ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int,void*) ; 
 int /*<<< orphan*/  set_pcb_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct proc_ldt* user_ldt_alloc (struct proc*,int /*<<< orphan*/ ) ; 

int
amd64_set_ldt(struct thread *td, struct i386_ldt_args *uap,
    struct user_segment_descriptor *descs)
{
	struct mdproc *mdp;
	struct proc_ldt *pldt;
	struct user_segment_descriptor *dp;
	struct proc *p;
	u_int largest_ld, i;
	int error;

#ifdef	DEBUG
	printf("amd64_set_ldt: start=%u num=%u descs=%p\n",
	    uap->start, uap->num, (void *)uap->descs);
#endif
	mdp = &td->td_proc->p_md;
	error = 0;

	set_pcb_flags(td->td_pcb, PCB_FULL_IRET);
	p = td->td_proc;
	if (descs == NULL) {
		/* Free descriptors */
		if (uap->start == 0 && uap->num == 0)
			uap->num = max_ldt_segment;
		if (uap->num == 0)
			return (EINVAL);
		if ((pldt = mdp->md_ldt) == NULL ||
		    uap->start >= max_ldt_segment)
			return (0);
		largest_ld = uap->start + uap->num;
		if (largest_ld > max_ldt_segment)
			largest_ld = max_ldt_segment;
		if (largest_ld < uap->start)
			return (EINVAL);
		mtx_lock(&dt_lock);
		for (i = uap->start; i < largest_ld; i++)
			((volatile uint64_t *)(pldt->ldt_base))[i] = 0;
		mtx_unlock(&dt_lock);
		return (0);
	}

	if (!(uap->start == LDT_AUTO_ALLOC && uap->num == 1)) {
		/* verify range of descriptors to modify */
		largest_ld = uap->start + uap->num;
		if (uap->start >= max_ldt_segment ||
		    largest_ld > max_ldt_segment ||
		    largest_ld < uap->start)
			return (EINVAL);
	}

	/* Check descriptors for access violations */
	for (i = 0; i < uap->num; i++) {
		dp = &descs[i];

		switch (dp->sd_type) {
		case SDT_SYSNULL:	/* system null */
			dp->sd_p = 0;
			break;
		case SDT_SYS286TSS:
		case SDT_SYSLDT:
		case SDT_SYS286BSY:
		case SDT_SYS286CGT:
		case SDT_SYSTASKGT:
		case SDT_SYS286IGT:
		case SDT_SYS286TGT:
		case SDT_SYSNULL2:
		case SDT_SYSTSS:
		case SDT_SYSNULL3:
		case SDT_SYSBSY:
		case SDT_SYSCGT:
		case SDT_SYSNULL4:
		case SDT_SYSIGT:
		case SDT_SYSTGT:
			return (EACCES);

		/* memory segment types */
		case SDT_MEMEC:   /* memory execute only conforming */
		case SDT_MEMEAC:  /* memory execute only accessed conforming */
		case SDT_MEMERC:  /* memory execute read conforming */
		case SDT_MEMERAC: /* memory execute read accessed conforming */
			 /* Must be "present" if executable and conforming. */
			if (dp->sd_p == 0)
				return (EACCES);
			break;
		case SDT_MEMRO:   /* memory read only */
		case SDT_MEMROA:  /* memory read only accessed */
		case SDT_MEMRW:   /* memory read write */
		case SDT_MEMRWA:  /* memory read write accessed */
		case SDT_MEMROD:  /* memory read only expand dwn limit */
		case SDT_MEMRODA: /* memory read only expand dwn lim accessed */
		case SDT_MEMRWD:  /* memory read write expand dwn limit */
		case SDT_MEMRWDA: /* memory read write expand dwn lim acessed */
		case SDT_MEME:    /* memory execute only */
		case SDT_MEMEA:   /* memory execute only accessed */
		case SDT_MEMER:   /* memory execute read */
		case SDT_MEMERA:  /* memory execute read accessed */
			break;
		default:
			return(EINVAL);
		}

		/* Only user (ring-3) descriptors may be present. */
		if ((dp->sd_p != 0) && (dp->sd_dpl != SEL_UPL))
			return (EACCES);
	}

	if (uap->start == LDT_AUTO_ALLOC && uap->num == 1) {
		/* Allocate a free slot */
		mtx_lock(&dt_lock);
		pldt = user_ldt_alloc(p, 0);
		if (pldt == NULL) {
			mtx_unlock(&dt_lock);
			return (ENOMEM);
		}

		/*
		 * start scanning a bit up to leave room for NVidia and
		 * Wine, which still user the "Blat" method of allocation.
		 */
		i = 16;
		dp = &((struct user_segment_descriptor *)(pldt->ldt_base))[i];
		for (; i < max_ldt_segment; ++i, ++dp) {
			if (dp->sd_type == SDT_SYSNULL)
				break;
		}
		if (i >= max_ldt_segment) {
			mtx_unlock(&dt_lock);
			return (ENOSPC);
		}
		uap->start = i;
		error = amd64_set_ldt_data(td, i, 1, descs);
		mtx_unlock(&dt_lock);
	} else {
		largest_ld = uap->start + uap->num;
		if (largest_ld > max_ldt_segment)
			return (EINVAL);
		mtx_lock(&dt_lock);
		if (user_ldt_alloc(p, 0) != NULL) {
			error = amd64_set_ldt_data(td, uap->start, uap->num,
			    descs);
		}
		mtx_unlock(&dt_lock);
	}
	if (error == 0)
		td->td_retval[0] = uap->start;
	return (error);
}
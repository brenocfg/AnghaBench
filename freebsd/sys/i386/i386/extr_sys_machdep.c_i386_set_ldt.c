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
struct TYPE_4__ {int sd_type; scalar_t__ sd_p; scalar_t__ sd_dpl; } ;
union descriptor {TYPE_2__ sd; } ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t u_int ;
struct thread {size_t* td_retval; TYPE_1__* td_proc; } ;
struct proc_ldt {size_t ldt_len; scalar_t__ ldt_base; } ;
struct mdproc {struct proc_ldt* md_ldt; } ;
struct i386_ldt_args {int start; int num; scalar_t__ descs; } ;
struct TYPE_3__ {struct mdproc p_md; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 size_t LDT_AUTO_ALLOC ; 
 size_t MAX_LD ; 
 int NLDT ; 
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
#define  SDT_SYS386BSY 138 
#define  SDT_SYS386CGT 137 
#define  SDT_SYS386IGT 136 
#define  SDT_SYS386TGT 135 
#define  SDT_SYS386TSS 134 
#define  SDT_SYSLDT 133 
#define  SDT_SYSNULL 132 
#define  SDT_SYSNULL2 131 
#define  SDT_SYSNULL3 130 
#define  SDT_SYSNULL4 129 
#define  SDT_SYSTASKGT 128 
 scalar_t__ SEL_UPL ; 
 int /*<<< orphan*/  atomic_store_rel_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_lock ; 
 int i386_ldt_grow (struct thread*,size_t) ; 
 int i386_set_ldt_data (struct thread*,size_t,int,union descriptor*) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int,void*) ; 

int
i386_set_ldt(struct thread *td, struct i386_ldt_args *uap,
    union descriptor *descs)
{
	struct mdproc *mdp;
	struct proc_ldt *pldt;
	union descriptor *dp;
	u_int largest_ld, i;
	int error;

#ifdef DEBUG
	printf("i386_set_ldt: start=%u num=%u descs=%p\n",
	    uap->start, uap->num, (void *)uap->descs);
#endif
	error = 0;
	mdp = &td->td_proc->p_md;

	if (descs == NULL) {
		/* Free descriptors */
		if (uap->start == 0 && uap->num == 0) {
			/*
			 * Treat this as a special case, so userland needn't
			 * know magic number NLDT.
			 */
			uap->start = NLDT;
			uap->num = MAX_LD - NLDT;
		}
		mtx_lock_spin(&dt_lock);
		if ((pldt = mdp->md_ldt) == NULL ||
		    uap->start >= pldt->ldt_len) {
			mtx_unlock_spin(&dt_lock);
			return (0);
		}
		largest_ld = uap->start + uap->num;
		if (largest_ld > pldt->ldt_len)
			largest_ld = pldt->ldt_len;
		for (i = uap->start; i < largest_ld; i++)
			atomic_store_rel_64(&((uint64_t *)(pldt->ldt_base))[i],
			    0);
		mtx_unlock_spin(&dt_lock);
		return (0);
	}

	if (uap->start != LDT_AUTO_ALLOC || uap->num != 1) {
		/* verify range of descriptors to modify */
		largest_ld = uap->start + uap->num;
		if (uap->start >= MAX_LD || largest_ld > MAX_LD)
			return (EINVAL);
	}

	/* Check descriptors for access violations */
	for (i = 0; i < uap->num; i++) {
		dp = &descs[i];

		switch (dp->sd.sd_type) {
		case SDT_SYSNULL:	/* system null */ 
			dp->sd.sd_p = 0;
			break;
		case SDT_SYS286TSS: /* system 286 TSS available */
		case SDT_SYSLDT:    /* system local descriptor table */
		case SDT_SYS286BSY: /* system 286 TSS busy */
		case SDT_SYSTASKGT: /* system task gate */
		case SDT_SYS286IGT: /* system 286 interrupt gate */
		case SDT_SYS286TGT: /* system 286 trap gate */
		case SDT_SYSNULL2:  /* undefined by Intel */ 
		case SDT_SYS386TSS: /* system 386 TSS available */
		case SDT_SYSNULL3:  /* undefined by Intel */
		case SDT_SYS386BSY: /* system 386 TSS busy */
		case SDT_SYSNULL4:  /* undefined by Intel */ 
		case SDT_SYS386IGT: /* system 386 interrupt gate */
		case SDT_SYS386TGT: /* system 386 trap gate */
		case SDT_SYS286CGT: /* system 286 call gate */ 
		case SDT_SYS386CGT: /* system 386 call gate */
			return (EACCES);

		/* memory segment types */
		case SDT_MEMEC:   /* memory execute only conforming */
		case SDT_MEMEAC:  /* memory execute only accessed conforming */
		case SDT_MEMERC:  /* memory execute read conforming */
		case SDT_MEMERAC: /* memory execute read accessed conforming */
			 /* Must be "present" if executable and conforming. */
			if (dp->sd.sd_p == 0)
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
			return (EINVAL);
		}

		/* Only user (ring-3) descriptors may be present. */
		if (dp->sd.sd_p != 0 && dp->sd.sd_dpl != SEL_UPL)
			return (EACCES);
	}

	if (uap->start == LDT_AUTO_ALLOC && uap->num == 1) {
		/* Allocate a free slot */
		mtx_lock_spin(&dt_lock);
		if ((pldt = mdp->md_ldt) == NULL) {
			if ((error = i386_ldt_grow(td, NLDT + 1))) {
				mtx_unlock_spin(&dt_lock);
				return (error);
			}
			pldt = mdp->md_ldt;
		}
again:
		/*
		 * start scanning a bit up to leave room for NVidia and
		 * Wine, which still user the "Blat" method of allocation.
		 */
		dp = &((union descriptor *)(pldt->ldt_base))[NLDT];
		for (i = NLDT; i < pldt->ldt_len; ++i) {
			if (dp->sd.sd_type == SDT_SYSNULL)
				break;
			dp++;
		}
		if (i >= pldt->ldt_len) {
			if ((error = i386_ldt_grow(td, pldt->ldt_len+1))) {
				mtx_unlock_spin(&dt_lock);
				return (error);
			}
			goto again;
		}
		uap->start = i;
		error = i386_set_ldt_data(td, i, 1, descs);
		mtx_unlock_spin(&dt_lock);
	} else {
		largest_ld = uap->start + uap->num;
		mtx_lock_spin(&dt_lock);
		if (!(error = i386_ldt_grow(td, largest_ld))) {
			error = i386_set_ldt_data(td, uap->start, uap->num,
			    descs);
		}
		mtx_unlock_spin(&dt_lock);
	}
	if (error == 0)
		td->td_retval[0] = uap->start;
	return (error);
}
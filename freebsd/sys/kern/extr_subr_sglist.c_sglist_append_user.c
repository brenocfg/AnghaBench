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
struct thread {TYPE_1__* td_proc; } ;
struct sgsave {int dummy; } ;
struct sglist {scalar_t__ sg_maxseg; } ;
struct TYPE_2__ {int /*<<< orphan*/  p_vmspace; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SGLIST_RESTORE (struct sglist*,struct sgsave) ; 
 int /*<<< orphan*/  SGLIST_SAVE (struct sglist*,struct sgsave) ; 
 int _sglist_append_buf (struct sglist*,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmspace_pmap (int /*<<< orphan*/ ) ; 

int
sglist_append_user(struct sglist *sg, void *buf, size_t len, struct thread *td)
{
	struct sgsave save;
	int error;

	if (sg->sg_maxseg == 0)
		return (EINVAL);
	SGLIST_SAVE(sg, save);
	error = _sglist_append_buf(sg, buf, len,
	    vmspace_pmap(td->td_proc->p_vmspace), NULL);
	if (error)
		SGLIST_RESTORE(sg, save);
	return (error);
}
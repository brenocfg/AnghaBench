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
typedef  int /*<<< orphan*/  uint64_t ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_gpa_pte {int ptenum; int /*<<< orphan*/ * pte; int /*<<< orphan*/  gpa; } ;
typedef  int /*<<< orphan*/  gpapte ;

/* Variables and functions */
 int /*<<< orphan*/  VM_GET_GPA_PMAP ; 
 int /*<<< orphan*/  bzero (struct vm_gpa_pte*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_gpa_pte*) ; 

int
vm_get_gpa_pmap(struct vmctx *ctx, uint64_t gpa, uint64_t *pte, int *num)
{
	int error, i;
	struct vm_gpa_pte gpapte;

	bzero(&gpapte, sizeof(gpapte));
	gpapte.gpa = gpa;

	error = ioctl(ctx->fd, VM_GET_GPA_PMAP, &gpapte);

	if (error == 0) {
		*num = gpapte.ptenum;
		for (i = 0; i < gpapte.ptenum; i++)
			pte[i] = gpapte.pte[i];
	}

	return (error);
}
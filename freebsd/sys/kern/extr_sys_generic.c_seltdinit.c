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
struct thread {struct seltd* td_sel; } ;
struct seltd {int /*<<< orphan*/  st_selq; scalar_t__ st_flags; int /*<<< orphan*/  st_wait; int /*<<< orphan*/  st_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_SELECT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 struct seltd* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
seltdinit(struct thread *td)
{
	struct seltd *stp;

	if ((stp = td->td_sel) != NULL)
		goto out;
	td->td_sel = stp = malloc(sizeof(*stp), M_SELECT, M_WAITOK|M_ZERO);
	mtx_init(&stp->st_mtx, "sellck", NULL, MTX_DEF);
	cv_init(&stp->st_wait, "select");
out:
	stp->st_flags = 0;
	STAILQ_INIT(&stp->st_selq);
}
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
struct mtx_args {int /*<<< orphan*/  ma_opts; int /*<<< orphan*/  ma_desc; scalar_t__ ma_mtx; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_init (struct mtx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mtx_sysinit(void *arg)
{
	struct mtx_args *margs = arg;

	mtx_init((struct mtx *)margs->ma_mtx, margs->ma_desc, NULL,
	    margs->ma_opts);
}
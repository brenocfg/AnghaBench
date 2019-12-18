#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xpparam_t ;
struct TYPE_8__ {int /*<<< orphan*/  nrec; } ;
struct TYPE_7__ {int /*<<< orphan*/  nrec; } ;
struct TYPE_9__ {TYPE_2__ xdf2; TYPE_1__ xdf1; } ;
typedef  TYPE_3__ xdfenv_t ;
typedef  int /*<<< orphan*/  mmfile_t ;

/* Variables and functions */
 int patience_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_3__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xdl_prepare_env (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_3__*) ; 

int xdl_do_patience_diff(mmfile_t *file1, mmfile_t *file2,
		xpparam_t const *xpp, xdfenv_t *env)
{
	if (xdl_prepare_env(file1, file2, xpp, env) < 0)
		return -1;

	/* environment is cleaned up in xdl_diff() */
	return patience_diff(file1, file2, xpp, env,
			1, env->xdf1.nrec, 1, env->xdf2.nrec);
}
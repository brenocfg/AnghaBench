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
struct TYPE_7__ {scalar_t__ dstart; scalar_t__ dend; } ;
struct TYPE_8__ {scalar_t__ dstart; scalar_t__ dend; } ;
struct TYPE_9__ {TYPE_1__ xdf2; TYPE_2__ xdf1; } ;
typedef  TYPE_3__ xdfenv_t ;
typedef  int /*<<< orphan*/  mmfile_t ;

/* Variables and functions */
 int histogram_diff (int /*<<< orphan*/  const*,TYPE_3__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ xdl_prepare_env (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_3__*) ; 

int xdl_do_histogram_diff(mmfile_t *file1, mmfile_t *file2,
	xpparam_t const *xpp, xdfenv_t *env)
{
	if (xdl_prepare_env(file1, file2, xpp, env) < 0)
		return -1;

	return histogram_diff(xpp, env,
		env->xdf1.dstart + 1, env->xdf1.dend - env->xdf1.dstart + 1,
		env->xdf2.dstart + 1, env->xdf2.dend - env->xdf2.dstart + 1);
}
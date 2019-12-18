#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int gl_flags; scalar_t__ (* gl_errfunc ) (char*,int) ;} ;
typedef  TYPE_1__ glob11_t ;

/* Variables and functions */
 int GLOB_ABORTED ; 
 int GLOB_ERR ; 
 scalar_t__ stub1 (char*,int) ; 

__attribute__((used)) static int
err_aborted(glob11_t *pglob, int err, char *buf) {
	if ((pglob->gl_errfunc != NULL && pglob->gl_errfunc(buf, err)) ||
	    (pglob->gl_flags & GLOB_ERR))
		return (GLOB_ABORTED);
	return (0);
}
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
struct cfe_xiocb {int dummy; } ;

/* Variables and functions */
 int cfe_dispfunc (intptr_t,intptr_t) ; 
 scalar_t__ cfe_handle ; 
 int stub1 (intptr_t,intptr_t) ; 

int cfe_iocb_dispatch(struct cfe_xiocb * xiocb)
{
	if (!cfe_dispfunc)
		return -1;
	return (*cfe_dispfunc) ((intptr_t) cfe_handle, (intptr_t) xiocb);
}
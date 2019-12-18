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
struct procdesc {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTYPE_PROCDESC ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  finit (struct file*,int,int /*<<< orphan*/ ,struct procdesc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  procdesc_ops ; 

void
procdesc_finit(struct procdesc *pdp, struct file *fp)
{

	finit(fp, FREAD | FWRITE, DTYPE_PROCDESC, pdp, &procdesc_ops);
}
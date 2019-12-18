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
typedef  int /*<<< orphan*/  GS ;
typedef  int /*<<< orphan*/  CL_PRIVATE ;

/* Variables and functions */
 int /*<<< orphan*/ * GCLP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_freecap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cl_ex_end(GS *gp)
{
	CL_PRIVATE *clp;

	clp = GCLP(gp);

	cl_freecap(clp);

	return (0);
}
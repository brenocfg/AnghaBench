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
struct pargs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PARGS ; 
 int /*<<< orphan*/  free (struct pargs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pargs_free(struct pargs *pa)
{

	free(pa, M_PARGS);
}
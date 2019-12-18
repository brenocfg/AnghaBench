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
struct sge_fl {int sidx; int /*<<< orphan*/  sdesc; } ;
struct fl_sdesc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CXGBE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
alloc_fl_sdesc(struct sge_fl *fl)
{

	fl->sdesc = malloc(fl->sidx * 8 * sizeof(struct fl_sdesc), M_CXGBE,
	    M_ZERO | M_WAITOK);

	return (0);
}
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
struct TYPE_3__ {scalar_t__ firstface; scalar_t__ numfaces; } ;
typedef  TYPE_1__ dmodel_t ;

/* Variables and functions */
 TYPE_1__* dmodels ; 
 scalar_t__ numfaces ; 
 size_t nummodels ; 

void EndModel (void)
{
	dmodel_t	*mod;

	mod = &dmodels[nummodels];

	mod->numfaces = numfaces - mod->firstface;

	nummodels++;
}
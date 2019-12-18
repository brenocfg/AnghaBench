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
struct dataset {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AdjPlot (scalar_t__) ; 
 scalar_t__ Avg (struct dataset*) ; 
 scalar_t__ Max (struct dataset*) ; 
 scalar_t__ Min (struct dataset*) ; 
 scalar_t__ Stddev (struct dataset*) ; 

__attribute__((used)) static void
DimPlot(struct dataset *ds)
{
	AdjPlot(Min(ds));
	AdjPlot(Max(ds));
	AdjPlot(Avg(ds) - Stddev(ds));
	AdjPlot(Avg(ds) + Stddev(ds));
}
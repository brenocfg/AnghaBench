#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fp_ext {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rnd; } ;

/* Variables and functions */
 TYPE_1__* FPDATA ; 
 int /*<<< orphan*/  PINSTR ; 
 int /*<<< orphan*/  dprint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fp_copy_ext (struct fp_ext*,struct fp_ext*) ; 
 int /*<<< orphan*/  fp_roundint (struct fp_ext*,int /*<<< orphan*/ ) ; 

struct fp_ext *
fp_fint(struct fp_ext *dest, struct fp_ext *src)
{
	dprint(PINSTR, "fint\n");

	fp_copy_ext(dest, src);

	fp_roundint(dest, FPDATA->rnd);

	return dest;
}
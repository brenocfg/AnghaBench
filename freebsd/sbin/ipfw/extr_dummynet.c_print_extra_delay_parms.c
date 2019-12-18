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
struct dn_profile {double samples_no; double loss_level; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,double,double) ; 

__attribute__((used)) static void
print_extra_delay_parms(struct dn_profile *p)
{
	double loss;
	if (p->samples_no <= 0)
		return;

	loss = p->loss_level;
	loss /= p->samples_no;
	printf("\t profile: name \"%s\" loss %f samples %d\n",
		p->name, loss, p->samples_no);
}
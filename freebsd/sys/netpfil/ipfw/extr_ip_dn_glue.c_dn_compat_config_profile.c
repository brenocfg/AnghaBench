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
struct dn_profile {int /*<<< orphan*/  samples; int /*<<< orphan*/  name; int /*<<< orphan*/  samples_no; int /*<<< orphan*/  loss_level; int /*<<< orphan*/  link_nr; } ;
struct dn_pipe_max8 {int /*<<< orphan*/ * samples; } ;
struct dn_pipe8 {int /*<<< orphan*/ * samples; int /*<<< orphan*/  name; int /*<<< orphan*/  samples_no; int /*<<< orphan*/  loss_level; } ;
struct dn_link {int /*<<< orphan*/  link_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dn_compat_config_profile(struct dn_profile *pf, struct dn_link *p,
			 void *v)
{
	struct dn_pipe8 *p8 = (struct dn_pipe8 *)v;

	p8->samples = &(((struct dn_pipe_max8 *)p8)->samples[0]);
	
	pf->link_nr = p->link_nr;
	pf->loss_level = p8->loss_level;
// 	pf->bandwidth = p->bandwidth; //XXX bandwidth redundant?
	pf->samples_no = p8->samples_no;
	strncpy(pf->name, p8->name,sizeof(pf->name));
	bcopy(p8->samples, pf->samples, sizeof(pf->samples));

	return 0;
}
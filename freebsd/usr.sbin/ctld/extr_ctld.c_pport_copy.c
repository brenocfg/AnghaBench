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
struct pport {int /*<<< orphan*/  pp_ctl_port; int /*<<< orphan*/  pp_name; } ;
struct conf {int dummy; } ;

/* Variables and functions */
 struct pport* pport_new (struct conf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct pport *
pport_copy(struct pport *pp, struct conf *conf)
{
	struct pport *ppnew;

	ppnew = pport_new(conf, pp->pp_name, pp->pp_ctl_port);
	return (ppnew);
}
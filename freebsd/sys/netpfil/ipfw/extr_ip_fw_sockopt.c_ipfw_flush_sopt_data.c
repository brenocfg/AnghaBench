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
struct sockopt_data {size_t koff; scalar_t__ ksize; scalar_t__ ktotal; scalar_t__ valsize; scalar_t__ kavail; scalar_t__ sopt_val; int /*<<< orphan*/  kbuf; struct sockopt* sopt; } ;
struct sockopt {scalar_t__ sopt_dir; scalar_t__ sopt_val; scalar_t__ sopt_valsize; } ;

/* Variables and functions */
 scalar_t__ SOPT_GET ; 
 int copyout (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
ipfw_flush_sopt_data(struct sockopt_data *sd)
{
	struct sockopt *sopt;
	int error;
	size_t sz;

	sz = sd->koff;
	if (sz == 0)
		return (0);

	sopt = sd->sopt;

	if (sopt->sopt_dir == SOPT_GET) {
		error = copyout(sd->kbuf, sopt->sopt_val, sz);
		if (error != 0)
			return (error);
	}

	memset(sd->kbuf, 0, sd->ksize);
	sd->ktotal += sz;
	sd->koff = 0;
	if (sd->ktotal + sd->ksize < sd->valsize)
		sd->kavail = sd->ksize;
	else
		sd->kavail = sd->valsize - sd->ktotal;

	/* Update sopt buffer data */
	sopt->sopt_valsize = sd->ktotal;
	sopt->sopt_val = sd->sopt_val + sd->ktotal;

	return (0);
}
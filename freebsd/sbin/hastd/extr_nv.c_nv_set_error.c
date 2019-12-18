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
struct nv {int nv_error; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NV_CHECK (struct nv*) ; 

int
nv_set_error(struct nv *nv, int error)
{
	int preverr;

	if (nv == NULL)
		return (ENOMEM);

	NV_CHECK(nv);

	preverr = nv->nv_error;
	nv->nv_error = error;
	return (preverr);
}
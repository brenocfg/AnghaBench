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
struct nv {int /*<<< orphan*/  nv_ebuf; scalar_t__ nv_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_CHECK (struct nv*) ; 
 int /*<<< orphan*/  ebuf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct nv*) ; 

void
nv_free(struct nv *nv)
{

	if (nv == NULL)
		return;

	NV_CHECK(nv);

	nv->nv_magic = 0;
	ebuf_free(nv->nv_ebuf);
	free(nv);
}
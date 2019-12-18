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
struct kerneldumpcomp {struct kerneldumpcomp* kdc_buf; int /*<<< orphan*/  kdc_stream; } ;
struct dumperinfo {int /*<<< orphan*/  maxiosize; struct kerneldumpcomp* kdcomp; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DUMPER ; 
 int /*<<< orphan*/  compressor_fini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  explicit_bzero (struct kerneldumpcomp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct kerneldumpcomp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kerneldumpcomp_destroy(struct dumperinfo *di)
{
	struct kerneldumpcomp *kdcomp;

	kdcomp = di->kdcomp;
	if (kdcomp == NULL)
		return;
	compressor_fini(kdcomp->kdc_stream);
	explicit_bzero(kdcomp->kdc_buf, di->maxiosize);
	free(kdcomp->kdc_buf, M_DUMPER);
	free(kdcomp, M_DUMPER);
}
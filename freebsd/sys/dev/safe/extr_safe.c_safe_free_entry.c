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
struct safe_softc {int dummy; } ;
struct TYPE_2__ {scalar_t__ d_csr; } ;
struct safe_ringentry {TYPE_1__ re_desc; scalar_t__ re_crp; int /*<<< orphan*/ * re_dst_m; int /*<<< orphan*/ * re_src_m; } ;
struct cryptop {int /*<<< orphan*/  crp_etype; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  crypto_done (struct cryptop*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
safe_free_entry(struct safe_softc *sc, struct safe_ringentry *re)
{
	struct cryptop *crp;

	/*
	 * Free header MCR
	 */
	if ((re->re_dst_m != NULL) && (re->re_src_m != re->re_dst_m))
		m_freem(re->re_dst_m);

	crp = (struct cryptop *)re->re_crp;
	
	re->re_desc.d_csr = 0;
	
	crp->crp_etype = EFAULT;
	crypto_done(crp);
	return(0);
}
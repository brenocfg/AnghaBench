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
typedef  void symkey_alloc ;
typedef  void symkey ;
struct TYPE_2__ {int /*<<< orphan*/  f; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_SLIST (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MEMINC ; 
 int /*<<< orphan*/  MOREMEM_EXTRA_ALLOC ; 
 int /*<<< orphan*/  authallocs ; 
 int /*<<< orphan*/  authfreekeys ; 
 int authnumfreekeys ; 
 void* eallocarrayxz (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 TYPE_1__ llink ; 

void
auth_moremem(
	int	keycount
	)
{
	symkey *	sk;
	int		i;
#ifdef DEBUG
	void *		base;
	symkey_alloc *	allocrec;
# define MOREMEM_EXTRA_ALLOC	(sizeof(*allocrec))
#else
# define MOREMEM_EXTRA_ALLOC	(0)
#endif

	i = (keycount > 0)
		? keycount
		: MEMINC;
	sk = eallocarrayxz(i, sizeof(*sk), MOREMEM_EXTRA_ALLOC);
#ifdef DEBUG
	base = sk;
#endif
	authnumfreekeys += i;

	for (; i > 0; i--, sk++) {
		LINK_SLIST(authfreekeys, sk, llink.f);
	}

#ifdef DEBUG
	allocrec = (void *)sk;
	allocrec->mem = base;
	LINK_SLIST(authallocs, allocrec, link);
#endif
}
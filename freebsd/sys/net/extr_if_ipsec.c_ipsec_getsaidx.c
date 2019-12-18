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
struct secpolicy {TYPE_1__** req; } ;
struct secasindex {int dummy; } ;
struct ipsec_softc {int dummy; } ;
typedef  int /*<<< orphan*/  sa_family_t ;
struct TYPE_2__ {struct secasindex saidx; } ;

/* Variables and functions */
 struct secpolicy* ipsec_getpolicy (struct ipsec_softc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct secasindex *
ipsec_getsaidx(struct ipsec_softc *sc, int dir, sa_family_t af)
{
	struct secpolicy *sp;

	sp = ipsec_getpolicy(sc, dir, af);
	if (sp == NULL)
		return (NULL);
	return (&sp->req[0]->saidx);
}
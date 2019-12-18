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
struct ath_ratectrl {int arc_space; } ;
struct onoe_softc {struct ath_ratectrl arc; } ;
struct onoe_node {int dummy; } ;
struct ath_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  ath_rate_sysctlattach (struct ath_softc*) ; 
 struct onoe_softc* malloc (int,int /*<<< orphan*/ ,int) ; 

struct ath_ratectrl *
ath_rate_attach(struct ath_softc *sc)
{
	struct onoe_softc *osc;

	osc = malloc(sizeof(struct onoe_softc), M_DEVBUF, M_NOWAIT|M_ZERO);
	if (osc == NULL)
		return NULL;
	osc->arc.arc_space = sizeof(struct onoe_node);
	ath_rate_sysctlattach(sc);

	return &osc->arc;
}
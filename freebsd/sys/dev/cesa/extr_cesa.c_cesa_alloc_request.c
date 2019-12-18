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
struct cesa_softc {int dummy; } ;
struct cesa_request {int /*<<< orphan*/  cr_sdesc; int /*<<< orphan*/  cr_tdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CESA_GENERIC_ALLOC_LOCKED (struct cesa_softc*,struct cesa_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  requests ; 

__attribute__((used)) static struct cesa_request *
cesa_alloc_request(struct cesa_softc *sc)
{
	struct cesa_request *cr;

	CESA_GENERIC_ALLOC_LOCKED(sc, cr, requests);
	if (!cr)
		return (NULL);

	STAILQ_INIT(&cr->cr_tdesc);
	STAILQ_INIT(&cr->cr_sdesc);

	return (cr);
}
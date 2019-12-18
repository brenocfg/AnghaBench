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
struct storvsc_softc {int /*<<< orphan*/  hs_free_list; } ;
struct hv_storvsc_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct hv_storvsc_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
storvsc_free_request(struct storvsc_softc *sc, struct hv_storvsc_request *reqp)
{

	LIST_INSERT_HEAD(&sc->hs_free_list, reqp, link);
}
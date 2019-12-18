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
struct vtblk_softc {int /*<<< orphan*/  vtblk_req_free; } ;
struct vtblk_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct vtblk_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbr_link ; 

__attribute__((used)) static void
vtblk_request_enqueue(struct vtblk_softc *sc, struct vtblk_request *req)
{

	TAILQ_INSERT_HEAD(&sc->vtblk_req_free, req, vbr_link);
}
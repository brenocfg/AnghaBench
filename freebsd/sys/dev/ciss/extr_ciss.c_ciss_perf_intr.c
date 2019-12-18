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
struct ciss_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISS_TL_PERF_CLEAR_INT (struct ciss_softc*) ; 
 int /*<<< orphan*/  CISS_TL_PERF_FLUSH_INT (struct ciss_softc*) ; 
 int /*<<< orphan*/  ciss_perf_msi_intr (struct ciss_softc*) ; 

__attribute__((used)) static void
ciss_perf_intr(void *arg)
{
    struct ciss_softc	*sc = (struct ciss_softc *)arg;

    /* Clear the interrupt and flush the bridges.  Docs say that the flush
     * needs to be done twice, which doesn't seem right.
     */
    CISS_TL_PERF_CLEAR_INT(sc);
    CISS_TL_PERF_FLUSH_INT(sc);

    ciss_perf_msi_intr(sc);
}
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
struct et_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct et_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ET_TXDMA_CTRL ; 
 int ET_TXDMA_CTRL_HALT ; 
 int ET_TXDMA_CTRL_SINGLE_EPKT ; 

__attribute__((used)) static int
et_stop_txdma(struct et_softc *sc)
{

	CSR_WRITE_4(sc, ET_TXDMA_CTRL,
		    ET_TXDMA_CTRL_HALT | ET_TXDMA_CTRL_SINGLE_EPKT);
	return (0);
}
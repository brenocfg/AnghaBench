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
typedef  int /*<<< orphan*/  uint32_t ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92C_TSFTR (int) ; 
 int /*<<< orphan*/  rtwn_read_4 (struct rtwn_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
rtwn_get_tsf_low(struct rtwn_softc *sc, int id)
{
	return (rtwn_read_4(sc, R92C_TSFTR(id)));
}
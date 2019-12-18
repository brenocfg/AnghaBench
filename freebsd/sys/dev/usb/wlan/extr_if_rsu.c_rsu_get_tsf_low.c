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
struct rsu_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92S_TSFTR ; 
 int /*<<< orphan*/  rsu_read_4 (struct rsu_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
rsu_get_tsf_low(struct rsu_softc *sc)
{
	return (rsu_read_4(sc, R92S_TSFTR));
}
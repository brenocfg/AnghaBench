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
typedef  int /*<<< orphan*/  uint8_t ;
struct cuda_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cuda_read_reg (struct cuda_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuda_write_reg (struct cuda_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vBufB ; 
 int /*<<< orphan*/  vPB4 ; 

__attribute__((used)) static void
cuda_toggle_ack(struct cuda_softc *sc)
{
	uint8_t reg;

	reg = cuda_read_reg(sc, vBufB);
	reg ^= vPB4;
	cuda_write_reg(sc, vBufB, reg);
}
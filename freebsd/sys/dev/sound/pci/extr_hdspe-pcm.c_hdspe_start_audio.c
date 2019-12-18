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
struct sc_info {int ctrl_register; } ;

/* Variables and functions */
 int HDSPE_AUDIO_INT_ENABLE ; 
 int /*<<< orphan*/  HDSPE_CONTROL_REG ; 
 int HDSPE_ENABLE ; 
 int /*<<< orphan*/  hdspe_write_4 (struct sc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
hdspe_start_audio(struct sc_info *sc)
{

	sc->ctrl_register |= (HDSPE_AUDIO_INT_ENABLE | HDSPE_ENABLE);
	hdspe_write_4(sc, HDSPE_CONTROL_REG, sc->ctrl_register);
}
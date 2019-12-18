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
struct audio_reg {int audio_clk; int /*<<< orphan*/  aval_reg; int /*<<< orphan*/  nval_reg; int /*<<< orphan*/  acr_reg; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int ERANGE ; 
 struct audio_reg* audio_regs ; 
 int nitems (struct audio_reg*) ; 

__attribute__((used)) static int
get_audio_regs(int freq, bus_size_t *acr_reg, bus_size_t *nval_reg,
    bus_size_t *aval_reg)
{
	int i;
	const struct audio_reg *reg;

	for (i = 0; i < nitems(audio_regs) ; i++) {
		reg = audio_regs + i;
		if (reg->audio_clk == freq) {
			if (acr_reg != NULL)
				*acr_reg = reg->acr_reg;
			if (nval_reg != NULL)
				*nval_reg = reg->nval_reg;
			if (aval_reg != NULL)
				*aval_reg = reg->aval_reg;
			return (0);
		}
	}
	return (ERANGE);
}
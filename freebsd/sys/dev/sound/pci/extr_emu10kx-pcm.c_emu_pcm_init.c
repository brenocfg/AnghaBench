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
struct emu_pcm_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  bufsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMUPAGESIZE ; 
 int /*<<< orphan*/  EMU_MAX_BUFSZ ; 
 int /*<<< orphan*/  EMU_REC_BUFSZ ; 
 int /*<<< orphan*/  pcm_getbuffersize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emu_pcm_init(struct emu_pcm_info *sc)
{
	sc->bufsz = pcm_getbuffersize(sc->dev, EMUPAGESIZE, EMU_REC_BUFSZ, EMU_MAX_BUFSZ);
	return (0);
}
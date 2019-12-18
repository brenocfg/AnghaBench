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
typedef  int u_int ;
struct i2s_softc {int output_mask; int /*<<< orphan*/  port_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  i2s_mute_headphone (struct i2s_softc*,int) ; 
 int /*<<< orphan*/  i2s_mute_lineout (struct i2s_softc*,int) ; 
 int /*<<< orphan*/  i2s_mute_speaker (struct i2s_softc*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
i2s_set_outputs(void *ptr, u_int mask)
{
	struct i2s_softc 	*sc = ptr;

	if (mask == sc->output_mask)
		return;

	mtx_lock(&sc->port_mtx);

	i2s_mute_speaker(sc, 1);
	i2s_mute_headphone(sc, 1);
	i2s_mute_lineout(sc, 1);

	DPRINTF(("enabled outputs: "));

	if (mask & (1 << 0)) {
		DPRINTF(("SPEAKER "));
		i2s_mute_speaker(sc, 0);
	} 
	if (mask & (1 << 1)) {
		DPRINTF(("HEADPHONE "));
		i2s_mute_headphone(sc, 0);
	}
	if (mask & (1 << 2)) {
		DPRINTF(("LINEOUT "));
		i2s_mute_lineout(sc, 0);
	}

	DPRINTF(("\n"));
	sc->output_mask = mask;

	mtx_unlock(&sc->port_mtx);
}
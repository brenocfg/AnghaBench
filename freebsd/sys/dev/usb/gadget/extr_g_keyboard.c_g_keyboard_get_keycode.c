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
typedef  int uint8_t ;
struct g_keyboard_softc {int sc_pattern_len; int* sc_pattern; } ;

/* Variables and functions */

__attribute__((used)) static uint8_t
g_keyboard_get_keycode(struct g_keyboard_softc *sc, int index)
{
	int key;
	int mod = sc->sc_pattern_len;

	if (mod == 0)
		index = 0;
	else
		index %= mod;

	if ((index >= 0) && (index < sc->sc_pattern_len))
		key = sc->sc_pattern[index];
	else
		key = 'a';

	if (key >= 'a' && key <= 'z')
		return (key - 'a' + 0x04);
	else
		return (0x04);
}
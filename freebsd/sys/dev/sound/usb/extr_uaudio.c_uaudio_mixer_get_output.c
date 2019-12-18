#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int id_max; int* bit_output; } ;
typedef  struct uaudio_terminal_node {TYPE_1__ usr; struct uaudio_terminal_node const* root; } const uaudio_terminal_node ;

/* Variables and functions */

__attribute__((used)) static const struct uaudio_terminal_node *
uaudio_mixer_get_output(const struct uaudio_terminal_node *iot, uint8_t i)
{
	struct uaudio_terminal_node *root = iot->root;
	uint8_t n;

	n = iot->usr.id_max;
	do {
		if (iot->usr.bit_output[n / 8] & (1 << (n % 8))) {
			if (!i--)
				return (root + n);
		}
	} while (n--);

	return (NULL);
}
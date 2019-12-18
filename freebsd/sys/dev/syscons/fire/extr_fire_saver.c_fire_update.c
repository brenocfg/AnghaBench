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
typedef  int /*<<< orphan*/  video_adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  SET_ORIGIN (int /*<<< orphan*/ *,int) ; 
 int banksize ; 
 int /*<<< orphan*/  bcopy (int*,scalar_t__,int) ; 
 int bpsl ; 
 int* buf ; 
 int random () ; 
 int scrh ; 
 int scrw ; 
 scalar_t__ vid ; 

__attribute__((used)) static void
fire_update(video_adapter_t *adp)
{
	int x, y;
	int o, p;
	int last_origin = -1;

	/* make a new bottom line */
	for (x = 0, y = scrh; x < scrw; x++)
		buf[x + (y * bpsl)] = random() % 160 + 96;

	/* fade the flames out */
	for (y = 0; y < scrh; y++) {
		for (x = 0; x < scrw; x++) {
			buf[x + (y * scrw)] =
			    (buf[(x + 0) + ((y + 0) * scrw)] +
			     buf[(x - 1) + ((y + 1) * scrw)] +
			     buf[(x + 0) + ((y + 1) * scrw)] +
			     buf[(x + 1) + ((y + 1) * scrw)]) / 4;
			if (buf[x + (y * scrw)] > 0)
				buf[x + (y * scrw)]--;
		}
	}

	/* blit our buffer into video ram */
	for (y = 0, p = 0, o = 0; y < scrh; y++, p += bpsl) {
		while (p > banksize) {
			p -= banksize;
			o += banksize;
		}
		SET_ORIGIN(adp, o);
		if (p + scrw < banksize) {
			bcopy(buf + y * scrw, vid + p, scrw);
		} else {
			bcopy(buf + y * scrw, vid + p, banksize - p);
			SET_ORIGIN(adp, o + banksize);
			bcopy(buf + y * scrw + (banksize - p), vid,
			      scrw - (banksize - p));
			p -= banksize;
			o += banksize;
		}
	}

}
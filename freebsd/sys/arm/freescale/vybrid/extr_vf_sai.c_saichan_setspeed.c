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
typedef  int uint32_t ;
struct sc_pcminfo {struct sc_info* sc; } ;
struct sc_info {struct sai_rate* sr; } ;
struct sc_chinfo {struct sc_pcminfo* parent; } ;
struct sai_rate {int speed; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 struct sai_rate* rate_map ; 
 int /*<<< orphan*/  sai_configure_clock (struct sc_info*) ; 

__attribute__((used)) static uint32_t
saichan_setspeed(kobj_t obj, void *data, uint32_t speed)
{
	struct sc_pcminfo *scp;
	struct sc_chinfo *ch;
	struct sai_rate *sr;
	struct sc_info *sc;
	int threshold;
	int i;

	ch = data;
	scp = ch->parent;
	sc = scp->sc;

	sr = NULL;

	/* First look for equal frequency. */
	for (i = 0; rate_map[i].speed != 0; i++) {
		if (rate_map[i].speed == speed)
			sr = &rate_map[i];
	}

	/* If no match, just find nearest. */
	if (sr == NULL) {
		for (i = 0; rate_map[i].speed != 0; i++) {
			sr = &rate_map[i];
			threshold = sr->speed + ((rate_map[i + 1].speed != 0) ?
			    ((rate_map[i + 1].speed - sr->speed) >> 1) : 0);
			if (speed < threshold)
				break;
		}
	}

	sc->sr = sr;

	sai_configure_clock(sc);

	return (sr->speed);
}
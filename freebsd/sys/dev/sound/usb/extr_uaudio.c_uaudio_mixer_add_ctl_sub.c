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
struct uaudio_softc {int /*<<< orphan*/  sc_mixer_count; struct uaudio_mixer_node* sc_mixer_root; } ;
struct uaudio_mixer_node {int nchan; int val_default; int* wData; int maxval; int minval; struct uaudio_mixer_node* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  M_USBDEV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct uaudio_mixer_node* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct uaudio_mixer_node*,struct uaudio_mixer_node*,int) ; 

__attribute__((used)) static void
uaudio_mixer_add_ctl_sub(struct uaudio_softc *sc, struct uaudio_mixer_node *mc)
{
	struct uaudio_mixer_node *p_mc_new =
	    malloc(sizeof(*p_mc_new), M_USBDEV, M_WAITOK);
	int ch;

	if (p_mc_new != NULL) {
		memcpy(p_mc_new, mc, sizeof(*p_mc_new));
		p_mc_new->next = sc->sc_mixer_root;
		sc->sc_mixer_root = p_mc_new;
		sc->sc_mixer_count++;

		/* set default value for all channels */
		for (ch = 0; ch < p_mc_new->nchan; ch++) {
			switch (p_mc_new->val_default) {
			case 1:
				/* 50% */
				p_mc_new->wData[ch] = (p_mc_new->maxval + p_mc_new->minval) / 2;
				break;
			case 2:
				/* 100% */
				p_mc_new->wData[ch] = p_mc_new->maxval;
				break;
			default:
				/* 0% */
				p_mc_new->wData[ch] = p_mc_new->minval;
				break;
			}
		}
	} else {
		DPRINTF("out of memory\n");
	}
}
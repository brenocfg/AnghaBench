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
struct uaudio_softc {struct uaudio_mixer_node* sc_mixer_root; } ;
struct uaudio_mixer_node {struct uaudio_mixer_node* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_USBDEV ; 
 int /*<<< orphan*/  free (struct uaudio_mixer_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uaudio_mixer_ctl_free(struct uaudio_softc *sc)
{
	struct uaudio_mixer_node *p_mc;

	while ((p_mc = sc->sc_mixer_root) != NULL) {
		sc->sc_mixer_root = p_mc->next;
		free(p_mc, M_USBDEV);
	}
}
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
struct uaudio_mixer_node {int nchan; char* name; int /*<<< orphan*/  desc; int /*<<< orphan*/  maxval; int /*<<< orphan*/  minval; int /*<<< orphan*/ * wValue; struct uaudio_mixer_node* next; } ;
struct sysctl_oid {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RWTUN ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct uaudio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,...) ; 
 int /*<<< orphan*/  uaudio_mixer_sysctl_handler ; 

__attribute__((used)) static void
uaudio_mixer_register_sysctl(struct uaudio_softc *sc, device_t dev)
{
	struct uaudio_mixer_node *pmc;
	struct sysctl_oid *mixer_tree;
	struct sysctl_oid *control_tree;
	char buf[32];
	int chan;
	int n;

	mixer_tree = SYSCTL_ADD_NODE(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO, "mixer",
	    CTLFLAG_RD, NULL, "");

	if (mixer_tree == NULL)
		return;

	for (n = 0, pmc = sc->sc_mixer_root; pmc != NULL;
	    pmc = pmc->next, n++) {

		for (chan = 0; chan < pmc->nchan; chan++) {

			if (pmc->nchan > 1) {
				snprintf(buf, sizeof(buf), "%s_%d_%d",
				    pmc->name, n, chan);
			} else {
				snprintf(buf, sizeof(buf), "%s_%d",
				    pmc->name, n);
			}

			control_tree = SYSCTL_ADD_NODE(device_get_sysctl_ctx(dev),
			    SYSCTL_CHILDREN(mixer_tree), OID_AUTO, buf,
			    CTLFLAG_RD, NULL, "Mixer control nodes");

			if (control_tree == NULL)
				continue;

			SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
			    SYSCTL_CHILDREN(control_tree),
			    OID_AUTO, "val", CTLTYPE_INT | CTLFLAG_RWTUN, sc,
			    pmc->wValue[chan],
			    uaudio_mixer_sysctl_handler, "I", "Current value");

			SYSCTL_ADD_INT(device_get_sysctl_ctx(dev),
			    SYSCTL_CHILDREN(control_tree),
			    OID_AUTO, "min", CTLFLAG_RD, 0, pmc->minval,
			    "Minimum value");

			SYSCTL_ADD_INT(device_get_sysctl_ctx(dev),
			    SYSCTL_CHILDREN(control_tree),
			    OID_AUTO, "max", CTLFLAG_RD, 0, pmc->maxval,
			    "Maximum value");

			SYSCTL_ADD_STRING(device_get_sysctl_ctx(dev),
			    SYSCTL_CHILDREN(control_tree),
			    OID_AUTO, "desc", CTLFLAG_RD, pmc->desc, 0,
			    "Description");
		}
	}
}
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
struct pinmux_softc {int dummy; } ;
struct pincfg {int* params; int /*<<< orphan*/ * function; } ;
typedef  int /*<<< orphan*/  phandle_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOENT ; 
 int OF_getencprop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int OF_getprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 
 int PROP_ID_MAX_ID ; 
 TYPE_1__* prop_names ; 

__attribute__((used)) static int
pinmux_read_node(struct pinmux_softc *sc, phandle_t node, struct pincfg *cfg,
    char **pins, int *lpins)
{
	int rv, i;

	*lpins = OF_getprop_alloc(node, "nvidia,pins", (void **)pins);
	if (*lpins <= 0)
		return (ENOENT);

	/* Read function (mux) settings. */
	rv = OF_getprop_alloc(node, "nvidia,function",
	    (void **)&cfg->function);
	if (rv <= 0)
		cfg->function = NULL;

	/* Read numeric properties. */
	for (i = 0; i < PROP_ID_MAX_ID; i++) {
		rv = OF_getencprop(node, prop_names[i].name, &cfg->params[i],
		    sizeof(cfg->params[i]));
		if (rv <= 0)
			cfg->params[i] = -1;
	}
	return (0);
}
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
struct ti_adc_softc {int sc_adc_nchannels; int* sc_adc_channels; int /*<<< orphan*/  value; int /*<<< orphan*/  sc_dev; } ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
typedef  int /*<<< orphan*/  pinbuf ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_UINT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,struct ti_adc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  ti_adc_clockdiv_proc ; 
 int /*<<< orphan*/  ti_adc_enable_proc ; 
 struct ti_adc_softc* ti_adc_inputs ; 
 int /*<<< orphan*/  ti_adc_open_delay_proc ; 
 int /*<<< orphan*/  ti_adc_samples_avg_proc ; 

__attribute__((used)) static void
ti_adc_sysctl_init(struct ti_adc_softc *sc)
{
	char pinbuf[3];
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *tree_node, *inp_node, *inpN_node;
	struct sysctl_oid_list *tree, *inp_tree, *inpN_tree;
	int ain, i;

	/*
	 * Add per-pin sysctl tree/handlers.
	 */
	ctx = device_get_sysctl_ctx(sc->sc_dev);
	tree_node = device_get_sysctl_tree(sc->sc_dev);
	tree = SYSCTL_CHILDREN(tree_node);
	SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "clockdiv",
	    CTLFLAG_RW | CTLTYPE_UINT,  sc, 0,
	    ti_adc_clockdiv_proc, "IU", "ADC clock prescaler");
	inp_node = SYSCTL_ADD_NODE(ctx, tree, OID_AUTO, "ain",
	    CTLFLAG_RD, NULL, "ADC inputs");
	inp_tree = SYSCTL_CHILDREN(inp_node);

	for (i = 0; i < sc->sc_adc_nchannels; i++) {
		ain = sc->sc_adc_channels[i];

		snprintf(pinbuf, sizeof(pinbuf), "%d", ain);
		inpN_node = SYSCTL_ADD_NODE(ctx, inp_tree, OID_AUTO, pinbuf,
		    CTLFLAG_RD, NULL, "ADC input");
		inpN_tree = SYSCTL_CHILDREN(inpN_node);

		SYSCTL_ADD_PROC(ctx, inpN_tree, OID_AUTO, "enable",
		    CTLFLAG_RW | CTLTYPE_UINT, &ti_adc_inputs[ain], 0,
		    ti_adc_enable_proc, "IU", "Enable ADC input");
		SYSCTL_ADD_PROC(ctx, inpN_tree, OID_AUTO, "open_delay",
		    CTLFLAG_RW | CTLTYPE_UINT,  &ti_adc_inputs[ain], 0,
		    ti_adc_open_delay_proc, "IU", "ADC open delay");
		SYSCTL_ADD_PROC(ctx, inpN_tree, OID_AUTO, "samples_avg",
		    CTLFLAG_RW | CTLTYPE_UINT,  &ti_adc_inputs[ain], 0,
		    ti_adc_samples_avg_proc, "IU", "ADC samples average");
		SYSCTL_ADD_INT(ctx, inpN_tree, OID_AUTO, "input",
		    CTLFLAG_RD, &ti_adc_inputs[ain].value, 0,
		    "Converted raw value for the ADC input");
	}
}
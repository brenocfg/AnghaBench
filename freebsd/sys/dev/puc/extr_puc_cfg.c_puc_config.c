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
struct puc_softc {struct puc_cfg* sc_cfg; } ;
struct puc_cfg {int (* config_function ) (struct puc_softc*,int,int,intptr_t*) ;intptr_t clock; int const ports; int d_ofs; intptr_t rid; int d_rid; int /*<<< orphan*/ * desc; } ;
typedef  enum puc_cfg_cmd { ____Placeholder_puc_cfg_cmd } puc_cfg_cmd ;

/* Variables and functions */
 int EDOOFUS ; 
 int ENXIO ; 
#define  PUC_CFG_GET_CLOCK 151 
#define  PUC_CFG_GET_DESC 150 
#define  PUC_CFG_GET_ILR 149 
#define  PUC_CFG_GET_LEN 148 
#define  PUC_CFG_GET_NPORTS 147 
#define  PUC_CFG_GET_OFS 146 
#define  PUC_CFG_GET_RID 145 
#define  PUC_CFG_GET_TYPE 144 
#define  PUC_CFG_SETUP 143 
 intptr_t PUC_ILR_NONE ; 
#define  PUC_PORT_12S 142 
#define  PUC_PORT_16S 141 
#define  PUC_PORT_1P 140 
#define  PUC_PORT_1S 139 
#define  PUC_PORT_1S1P 138 
#define  PUC_PORT_1S2P 137 
#define  PUC_PORT_2P 136 
#define  PUC_PORT_2S 135 
#define  PUC_PORT_2S1P 134 
#define  PUC_PORT_3S 133 
#define  PUC_PORT_4S 132 
#define  PUC_PORT_4S1P 131 
#define  PUC_PORT_6S 130 
#define  PUC_PORT_8S 129 
#define  PUC_PORT_NONSTANDARD 128 
 intptr_t PUC_TYPE_PARALLEL ; 
 intptr_t PUC_TYPE_SERIAL ; 
 int stub1 (struct puc_softc*,int,int,intptr_t*) ; 

int
puc_config(struct puc_softc *sc, enum puc_cfg_cmd cmd, int port, intptr_t *r)
{
	const struct puc_cfg *cfg = sc->sc_cfg;
	int error;

	if (cfg->config_function != NULL) {
		error = cfg->config_function(sc, cmd, port, r);
		if (!error)
			return (0);
	} else
		error = EDOOFUS;

	switch (cmd) {
	case PUC_CFG_GET_CLOCK:
		if (cfg->clock < 0)
			return (error);
		*r = cfg->clock;
		return (0);
	case PUC_CFG_GET_DESC:
		if (cfg->desc == NULL)
			return (error);
		*r = (intptr_t)cfg->desc;
		return (0);
	case PUC_CFG_GET_ILR:
		*r = PUC_ILR_NONE;
		return (0);
	case PUC_CFG_GET_LEN:
		/* The length of bus space needed by the port. */
		*r = 8;
		return (0);
	case PUC_CFG_GET_NPORTS:
		/* The number of ports on this card. */
		switch (cfg->ports) {
		case PUC_PORT_NONSTANDARD:
			return (error);
		case PUC_PORT_1P:
		case PUC_PORT_1S:
			*r = 1;
			return (0);
		case PUC_PORT_1S1P:
		case PUC_PORT_2P:
		case PUC_PORT_2S:
			*r = 2;
			return (0);
		case PUC_PORT_1S2P:
		case PUC_PORT_2S1P:
		case PUC_PORT_3S:
			*r = 3;
			return (0);
		case PUC_PORT_4S:
			*r = 4;
			return (0);
		case PUC_PORT_4S1P:
			*r = 5;
			return (0);
		case PUC_PORT_6S:
			*r = 6;
			return (0);
		case PUC_PORT_8S:
			*r = 8;
			return (0);
		case PUC_PORT_12S:
			*r = 12;
			return (0);
		case PUC_PORT_16S:
			*r = 16;
			return (0);
		}
		break;
	case PUC_CFG_GET_OFS:
		/* The offset relative to the RID. */
		if (cfg->d_ofs < 0)
			return (error);
		*r = port * cfg->d_ofs;
		return (0);
	case PUC_CFG_GET_RID:
		/* The RID for this port. */
		if (port == 0) {
			if (cfg->rid < 0)
				return (error);
			*r = cfg->rid;
			return (0);
		}
		if (cfg->d_rid < 0)
			return (error);
		if (cfg->rid < 0) {
			error = puc_config(sc, PUC_CFG_GET_RID, 0, r);
			if (error)
				return (error);
		} else
			*r = cfg->rid;
		*r += port * cfg->d_rid;
		return (0);
	case PUC_CFG_GET_TYPE:
		/* The type of this port. */
		if (cfg->ports == PUC_PORT_NONSTANDARD)
			return (error);
		switch (port) {
		case 0:
			if (cfg->ports == PUC_PORT_1P ||
			    cfg->ports == PUC_PORT_2P)
				*r = PUC_TYPE_PARALLEL;
			else
				*r = PUC_TYPE_SERIAL;
			return (0);
		case 1:
			if (cfg->ports == PUC_PORT_1S1P ||
			    cfg->ports == PUC_PORT_1S2P ||
			    cfg->ports == PUC_PORT_2P)
				*r = PUC_TYPE_PARALLEL;
			else
				*r = PUC_TYPE_SERIAL;
			return (0);
		case 2:
			if (cfg->ports == PUC_PORT_1S2P ||
			    cfg->ports == PUC_PORT_2S1P)
				*r = PUC_TYPE_PARALLEL;
			else
				*r = PUC_TYPE_SERIAL;
			return (0);
		case 4:
			if (cfg->ports == PUC_PORT_4S1P)
				*r = PUC_TYPE_PARALLEL;
			else
				*r = PUC_TYPE_SERIAL;
			return (0);
		}
		*r = PUC_TYPE_SERIAL;
		return (0);
	case PUC_CFG_SETUP:
		*r = ENXIO;
		return (0);
	}

	return (ENXIO);
}
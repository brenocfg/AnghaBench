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
typedef  int uint16_t ;
struct puc_softc {intptr_t sc_cfg_data; int /*<<< orphan*/  sc_dev; } ;
typedef  enum puc_cfg_cmd { ____Placeholder_puc_cfg_cmd } puc_cfg_cmd ;
typedef  int /*<<< orphan*/  desc ;

/* Variables and functions */
 int DEFAULT_RCLK ; 
 int ENXIO ; 
#define  PUC_CFG_GET_CLOCK 133 
#define  PUC_CFG_GET_DESC 132 
#define  PUC_CFG_GET_NPORTS 131 
#define  PUC_CFG_GET_OFS 130 
#define  PUC_CFG_GET_RID 129 
#define  PUC_CFG_GET_TYPE 128 
 intptr_t PUC_TYPE_SERIAL ; 
 int pci_get_subdevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
puc_config_timedia(struct puc_softc *sc, enum puc_cfg_cmd cmd, int port,
    intptr_t *res)
{
	static const uint16_t dual[] = {
	    0x0002, 0x4036, 0x4037, 0x4038, 0x4078, 0x4079, 0x4085,
	    0x4088, 0x4089, 0x5037, 0x5078, 0x5079, 0x5085, 0x6079,
	    0x7079, 0x8079, 0x8137, 0x8138, 0x8237, 0x8238, 0x9079,
	    0x9137, 0x9138, 0x9237, 0x9238, 0xA079, 0xB079, 0xC079,
	    0xD079, 0
	};
	static const uint16_t quad[] = {
	    0x4055, 0x4056, 0x4095, 0x4096, 0x5056, 0x8156, 0x8157,
	    0x8256, 0x8257, 0x9056, 0x9156, 0x9157, 0x9158, 0x9159,
	    0x9256, 0x9257, 0xA056, 0xA157, 0xA158, 0xA159, 0xB056,
	    0xB157, 0
	};
	static const uint16_t octa[] = {
	    0x4065, 0x4066, 0x5065, 0x5066, 0x8166, 0x9066, 0x9166,
	    0x9167, 0x9168, 0xA066, 0xA167, 0xA168, 0
	};
	static const struct {
		int ports;
		const uint16_t *ids;
	} subdevs[] = {
	    { 2, dual },
	    { 4, quad },
	    { 8, octa },
	    { 0, NULL }
	};
	static char desc[64];
	int dev, id;
	uint16_t subdev;

	switch (cmd) {
	case PUC_CFG_GET_CLOCK:
		if (port < 2)
			*res = DEFAULT_RCLK * 8;
		else
			*res = DEFAULT_RCLK;
		return (0);
	case PUC_CFG_GET_DESC:
		snprintf(desc, sizeof(desc),
		    "Timedia technology %d Port Serial", (int)sc->sc_cfg_data);
		*res = (intptr_t)desc;
		return (0);
	case PUC_CFG_GET_NPORTS:
		subdev = pci_get_subdevice(sc->sc_dev);
		dev = 0;
		while (subdevs[dev].ports != 0) {
			id = 0;
			while (subdevs[dev].ids[id] != 0) {
				if (subdev == subdevs[dev].ids[id]) {
					sc->sc_cfg_data = subdevs[dev].ports;
					*res = sc->sc_cfg_data;
					return (0);
				}
				id++;
			}
			dev++;
		}
		return (ENXIO);
	case PUC_CFG_GET_OFS:
		*res = (port == 1 || port == 3) ? 8 : 0;
		return (0);
	case PUC_CFG_GET_RID:
		*res = 0x10 + ((port > 3) ? port - 2 : port >> 1) * 4;
		return (0);
	case PUC_CFG_GET_TYPE:
		*res = PUC_TYPE_SERIAL;
		return (0);
	default:
		break;
	}
	return (ENXIO);
}
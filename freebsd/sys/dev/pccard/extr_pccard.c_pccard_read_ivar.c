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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int prodext; char** cis1_info; int /*<<< orphan*/  product; int /*<<< orphan*/  manufacturer; } ;
struct pccard_softc {TYPE_1__ card; } ;
struct pccard_ivar {struct pccard_function* pf; } ;
struct pccard_function {int pf_funce_disk_interface; int pf_funce_disk_power; int /*<<< orphan*/  number; int /*<<< orphan*/  function; int /*<<< orphan*/  pf_funce_lan_nid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 struct pccard_ivar* PCCARD_IVAR (int /*<<< orphan*/ ) ; 
#define  PCCARD_IVAR_CIS3_STR 138 
#define  PCCARD_IVAR_CIS4_STR 137 
#define  PCCARD_IVAR_ETHADDR 136 
#define  PCCARD_IVAR_FUNCE_DISK 135 
#define  PCCARD_IVAR_FUNCTION 134 
#define  PCCARD_IVAR_FUNCTION_NUMBER 133 
#define  PCCARD_IVAR_PRODEXT 132 
#define  PCCARD_IVAR_PRODUCT 131 
#define  PCCARD_IVAR_PRODUCT_STR 130 
#define  PCCARD_IVAR_VENDOR 129 
#define  PCCARD_IVAR_VENDOR_STR 128 
 struct pccard_softc* PCCARD_SOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,uintptr_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
pccard_read_ivar(device_t bus, device_t child, int which, uintptr_t *result)
{
	struct pccard_ivar *devi = PCCARD_IVAR(child);
	struct pccard_function *pf = devi->pf;
	struct pccard_softc *sc = PCCARD_SOFTC(bus);

	if (!pf)
		panic("No pccard function pointer");
	switch (which) {
	default:
		return (EINVAL);
	case PCCARD_IVAR_FUNCE_DISK:
		*(uint16_t *)result = pf->pf_funce_disk_interface |
		    (pf->pf_funce_disk_power << 8);
		break;
	case PCCARD_IVAR_ETHADDR:
		bcopy(pf->pf_funce_lan_nid, result, ETHER_ADDR_LEN);
		break;
	case PCCARD_IVAR_VENDOR:
		*(uint32_t *)result = sc->card.manufacturer;
		break;
	case PCCARD_IVAR_PRODUCT:
		*(uint32_t *)result = sc->card.product;
		break;
	case PCCARD_IVAR_PRODEXT:
		*(uint16_t *)result = sc->card.prodext;
		break;
	case PCCARD_IVAR_FUNCTION:
		*(uint32_t *)result = pf->function;
		break;
	case PCCARD_IVAR_FUNCTION_NUMBER:
		*(uint32_t *)result = pf->number;
		break;
	case PCCARD_IVAR_VENDOR_STR:
		*(const char **)result = sc->card.cis1_info[0];
		break;
	case PCCARD_IVAR_PRODUCT_STR:
		*(const char **)result = sc->card.cis1_info[1];
		break;
	case PCCARD_IVAR_CIS3_STR:
		*(const char **)result = sc->card.cis1_info[2];
		break;
	case PCCARD_IVAR_CIS4_STR:
		*(const char **)result = sc->card.cis1_info[3];
		break;
	}
	return (0);
}
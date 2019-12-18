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
struct sndcard_func {uintptr_t func; int /*<<< orphan*/ * varinfo; } ;
struct emu_sc_info {uintptr_t is_emu10k1; uintptr_t mch_disabled; uintptr_t mch_rec; } ;
struct emu_pcminfo {uintptr_t route; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  EMU_VAR_FUNC 132 
#define  EMU_VAR_ISEMU10K1 131 
#define  EMU_VAR_MCH_DISABLED 130 
#define  EMU_VAR_MCH_REC 129 
#define  EMU_VAR_ROUTE 128 
 int ENOENT ; 
 int ENOMEM ; 
 struct sndcard_func* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct emu_sc_info* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emu_read_ivar(device_t bus, device_t dev, int ivar_index, uintptr_t * result)
{
	struct sndcard_func *func = device_get_ivars(dev);
	struct emu_sc_info *sc = device_get_softc(bus);

	if (func==NULL)
		return (ENOMEM);
	if (sc == NULL)
		return (ENOMEM);

	switch (ivar_index) {
	case EMU_VAR_FUNC:
		*result = func->func;
		break;
	case EMU_VAR_ROUTE:
		if (func->varinfo == NULL)
			return (ENOMEM);
		*result = ((struct emu_pcminfo *)func->varinfo)->route;
		break;
	case EMU_VAR_ISEMU10K1:
		*result = sc->is_emu10k1;
		break;
	case EMU_VAR_MCH_DISABLED:
		*result = sc->mch_disabled;
		break;
	case EMU_VAR_MCH_REC:
		*result = sc->mch_rec;
		break;
	default:
		return (ENOENT);
	}

	return (0);
}
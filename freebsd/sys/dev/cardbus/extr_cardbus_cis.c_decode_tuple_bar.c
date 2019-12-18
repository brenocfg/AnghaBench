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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct tuple_callbacks {int dummy; } ;
struct cardbus_devinfo {int mprefetchable; int mbelow1mb; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int PCIR_BAR (int) ; 
 int PCI_RID2BAR (int) ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 int TPL_BAR_REG_AS ; 
 int TPL_BAR_REG_ASI_MASK ; 
 int TPL_BAR_REG_BELOW1MB ; 
 int TPL_BAR_REG_PREFETCHABLE ; 
 struct cardbus_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int le32toh (int) ; 

__attribute__((used)) static int
decode_tuple_bar(device_t cbdev, device_t child, int id,
    int len, uint8_t *tupledata, uint32_t start, uint32_t *off,
    struct tuple_callbacks *info, void *argp)
{
	struct cardbus_devinfo *dinfo = device_get_ivars(child);
	int type;
	uint8_t reg;
	uint32_t bar;

	if (len != 6) {
		device_printf(cbdev, "CIS BAR length not 6 (%d)\n", len);
		return (EINVAL);
	}

	reg = *tupledata;
	len = le32toh(*(uint32_t*)(tupledata + 2));
	if (reg & TPL_BAR_REG_AS)
		type = SYS_RES_IOPORT;
	else
		type = SYS_RES_MEMORY;

	bar = reg & TPL_BAR_REG_ASI_MASK;
	if (bar == 0) {
		device_printf(cbdev, "Invalid BAR type 0 in CIS\n");
		return (EINVAL);	/* XXX Return an error? */
	} else if (bar == 7) {
		/* XXX Should we try to map in Option ROMs? */
		return (0);
	}

	/* Convert from BAR type to BAR offset */
	bar = PCIR_BAR(bar - 1);

	if (type == SYS_RES_MEMORY) {
		if (reg & TPL_BAR_REG_PREFETCHABLE)
			dinfo->mprefetchable |= (1 << PCI_RID2BAR(bar));
		/*
		 * The PC Card spec says we're only supposed to honor this
		 * hint when the cardbus bridge is a child of pci0 (the main
		 * bus).  The PC Card spec seems to indicate that this should
		 * only be done on x86 based machines, which suggests that on
		 * non-x86 machines the addresses can be anywhere.  Since the
		 * hardware can do it on non-x86 machines, it should be able
		 * to do it on x86 machines too.  Therefore, we can and should
		 * ignore this hint.  Furthermore, the PC Card spec recommends
		 * always allocating memory above 1MB, contradicting the other
		 * part of the PC Card spec, it seems.  We make note of it,
		 * but otherwise don't use this information.
		 *
		 * Some Realtek cards have this set in their CIS, but fail
		 * to actually work when mapped this way, and experience
		 * has shown ignoring this big to be a wise choice.
		 *
		 * XXX We should cite chapter and verse for standard refs.
		 */
		if (reg & TPL_BAR_REG_BELOW1MB)
			dinfo->mbelow1mb |= (1 << PCI_RID2BAR(bar));
	}

	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int tcode; } ;
struct TYPE_5__ {void** ld; TYPE_1__ common; } ;
struct fw_pkt {TYPE_2__ mode; } ;
struct TYPE_6__ {int hdr_len; } ;

/* Variables and functions */
#define  FWOHCITCODE_PHY 137 
 void* FWOHCI_DMA_READ (void*) ; 
#define  FWTCODE_LREQ 136 
#define  FWTCODE_LRES 135 
#define  FWTCODE_RREQB 134 
#define  FWTCODE_RREQQ 133 
#define  FWTCODE_RRESB 132 
#define  FWTCODE_RRESQ 131 
#define  FWTCODE_WREQB 130 
#define  FWTCODE_WREQQ 129 
#define  FWTCODE_WRES 128 
 scalar_t__ firewire_debug ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_3__* tinfo ; 

__attribute__((used)) static int
fwohci_arcv_swap(struct fw_pkt *fp, int len)
{
	struct fw_pkt *fp0;
	uint32_t ld0;
	int slen, hlen;
#if BYTE_ORDER == BIG_ENDIAN
	int i;
#endif

	ld0 = FWOHCI_DMA_READ(fp->mode.ld[0]);
#if 0
	printf("ld0: x%08x\n", ld0);
#endif
	fp0 = (struct fw_pkt *)&ld0;
	/* determine length to swap */
	switch (fp0->mode.common.tcode) {
	case FWTCODE_RREQQ:
	case FWTCODE_WRES:
	case FWTCODE_WREQQ:
	case FWTCODE_RRESQ:
	case FWOHCITCODE_PHY:
		slen = 12;
		break;
	case FWTCODE_RREQB:
	case FWTCODE_WREQB:
	case FWTCODE_LREQ:
	case FWTCODE_RRESB:
	case FWTCODE_LRES:
		slen = 16;
		break;
	default:
		printf("Unknown tcode %d\n", fp0->mode.common.tcode);
		return (0);
	}
	hlen = tinfo[fp0->mode.common.tcode].hdr_len;
	if (hlen > len) {
		if (firewire_debug)
			printf("splitted header\n");
		return (-hlen);
	}
#if BYTE_ORDER == BIG_ENDIAN
	for (i = 0; i < slen/4; i++)
		fp->mode.ld[i] = FWOHCI_DMA_READ(fp->mode.ld[i]);
#endif
	return (hlen);
}
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
typedef  size_t uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct hda_stream_desc {int run; int bdl_cnt; size_t stream; size_t dir; scalar_t__ be; scalar_t__ bp; struct hda_bdle_desc* bdl; } ;
struct hda_softc {size_t** stream_map; struct hda_stream_desc* streams; } ;
struct hda_bdle_desc {int len; int /*<<< orphan*/  ioc; void* addr; } ;
struct hda_bdle {int len; int addrl; int addrh; int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int HDAC_SDBDPL ; 
 int HDAC_SDBDPU ; 
 int HDAC_SDCTL0 ; 
 int HDAC_SDLVI ; 
 int HDA_BDL_ENTRY_LEN ; 
 int HDA_BDL_MAX_LEN ; 
 int HDA_DMA_ACCESS_LEN ; 
 size_t HDA_ISS_NO ; 
 int /*<<< orphan*/  assert (int) ; 
 void* hda_dma_get_vaddr (struct hda_softc*,int,int) ; 
 int hda_get_offset_stream (size_t) ; 
 int hda_get_reg_by_offset (struct hda_softc*,int) ; 
 int /*<<< orphan*/  hda_notify_codecs (struct hda_softc*,int,size_t,size_t) ; 
 int /*<<< orphan*/  hda_set_pib (struct hda_softc*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hda_stream_start(struct hda_softc *sc, uint8_t stream_ind)
{
	struct hda_stream_desc *st = &sc->streams[stream_ind];
	struct hda_bdle_desc *bdle_desc = NULL;
	struct hda_bdle *bdle = NULL;
	uint32_t lvi = 0;
	uint32_t bdl_cnt = 0;
	uint64_t bdpl = 0;
	uint64_t bdpu = 0;
	uint64_t bdl_paddr = 0;
	void *bdl_vaddr = NULL;
	uint32_t bdle_sz = 0;
	uint64_t bdle_addrl = 0;
	uint64_t bdle_addrh = 0;
	uint64_t bdle_paddr = 0;
	void *bdle_vaddr = NULL;
	uint32_t off = hda_get_offset_stream(stream_ind);
	uint32_t sdctl = 0;
	uint8_t strm = 0;
	uint8_t dir = 0;
	int i;

	assert(!st->run);

	lvi = hda_get_reg_by_offset(sc, off + HDAC_SDLVI);
	bdpl = hda_get_reg_by_offset(sc, off + HDAC_SDBDPL);
	bdpu = hda_get_reg_by_offset(sc, off + HDAC_SDBDPU);

	bdl_cnt = lvi + 1;
	assert(bdl_cnt <= HDA_BDL_MAX_LEN);

	bdl_paddr = bdpl | (bdpu << 32);
	bdl_vaddr = hda_dma_get_vaddr(sc, bdl_paddr,
	    HDA_BDL_ENTRY_LEN * bdl_cnt);
	if (!bdl_vaddr) {
		DPRINTF("Fail to get the guest virtual address\n");
		return (-1);
	}

	DPRINTF("stream: 0x%x bdl_cnt: 0x%x bdl_paddr: 0x%lx\n",
	    stream_ind, bdl_cnt, bdl_paddr);

	st->bdl_cnt = bdl_cnt;

	bdle = (struct hda_bdle *)bdl_vaddr;
	for (i = 0; i < bdl_cnt; i++, bdle++) {
		bdle_sz = bdle->len;
		assert(!(bdle_sz % HDA_DMA_ACCESS_LEN));

		bdle_addrl = bdle->addrl;
		bdle_addrh = bdle->addrh;

		bdle_paddr = bdle_addrl | (bdle_addrh << 32);
		bdle_vaddr = hda_dma_get_vaddr(sc, bdle_paddr, bdle_sz);
		if (!bdle_vaddr) {
			DPRINTF("Fail to get the guest virtual address\n");
			return (-1);
		}

		bdle_desc = &st->bdl[i];
		bdle_desc->addr = bdle_vaddr;
		bdle_desc->len = bdle_sz;
		bdle_desc->ioc = bdle->ioc;

		DPRINTF("bdle: 0x%x bdle_sz: 0x%x\n", i, bdle_sz);
	}

	sdctl = hda_get_reg_by_offset(sc, off + HDAC_SDCTL0);
	strm = (sdctl >> 20) & 0x0f;
	dir = stream_ind >= HDA_ISS_NO;

	DPRINTF("strm: 0x%x, dir: 0x%x\n", strm, dir);

	sc->stream_map[dir][strm] = stream_ind;
	st->stream = strm;
	st->dir = dir;
	st->bp = 0;
	st->be = 0;

	hda_set_pib(sc, stream_ind, 0);

	st->run = 1;

	hda_notify_codecs(sc, 1, strm, dir);

	return (0);
}
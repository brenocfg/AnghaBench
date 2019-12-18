#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int size; scalar_t__ stream_id; scalar_t__ inst_be; } ;
union zip_quex_sbuf_ctl {unsigned long long u_reg64; TYPE_3__ s; } ;
struct TYPE_12__ {int ptr; } ;
union zip_quex_sbuf_addr {unsigned long long u_reg64; TYPE_4__ s; } ;
struct TYPE_14__ {int zce; } ;
union zip_quex_map {unsigned long long u_reg64; TYPE_6__ s; } ;
struct TYPE_15__ {int pri; } ;
union zip_que_pri {unsigned long long u_reg64; TYPE_7__ s; } ;
struct TYPE_13__ {int ena; } ;
union zip_que_ena {int u_reg64; TYPE_5__ s; } ;
struct TYPE_10__ {int /*<<< orphan*/  ctxsize; int /*<<< orphan*/  onfsize; int /*<<< orphan*/  depth; } ;
union zip_constants {TYPE_2__ s; void* u_reg64; } ;
struct TYPE_9__ {int forceclk; } ;
union zip_cmd_ctl {int u_reg64; TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  u64 ;
struct zip_iq {int dummy; } ;
struct zip_device {scalar_t__ reg_base; TYPE_8__* iq; int /*<<< orphan*/  ctxsize; int /*<<< orphan*/  onfsize; int /*<<< orphan*/  depth; } ;
struct TYPE_16__ {int /*<<< orphan*/  hw_tail; int /*<<< orphan*/  sw_tail; int /*<<< orphan*/  sw_head; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ZIP_128B_ALIGN ; 
 scalar_t__ ZIP_CMD_CTL ; 
 int ZIP_CMD_QBUF_SIZE ; 
 scalar_t__ ZIP_CONSTANTS ; 
 int ZIP_NUM_QUEUES ; 
 scalar_t__ ZIP_QUEX_MAP (int) ; 
 scalar_t__ ZIP_QUEX_SBUF_ADDR (int) ; 
 scalar_t__ ZIP_QUEX_SBUF_CTL (int) ; 
 scalar_t__ ZIP_QUE_ENA ; 
 scalar_t__ ZIP_QUE_PRI ; 
 int __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ zip_cmd_qbuf_alloc (struct zip_device*,int) ; 
 int /*<<< orphan*/  zip_cmd_qbuf_free (struct zip_device*,int) ; 
 int /*<<< orphan*/  zip_dbg (char*,int,...) ; 
 int /*<<< orphan*/  zip_msg (char*,void*,...) ; 
 void* zip_reg_read (scalar_t__) ; 
 int /*<<< orphan*/  zip_reg_write (int,scalar_t__) ; 

__attribute__((used)) static int zip_init_hw(struct zip_device *zip)
{
	union zip_cmd_ctl    cmd_ctl;
	union zip_constants  constants;
	union zip_que_ena    que_ena;
	union zip_quex_map   que_map;
	union zip_que_pri    que_pri;

	union zip_quex_sbuf_addr que_sbuf_addr;
	union zip_quex_sbuf_ctl  que_sbuf_ctl;

	int q = 0;

	/* Enable the ZIP Engine(Core) Clock */
	cmd_ctl.u_reg64 = zip_reg_read(zip->reg_base + ZIP_CMD_CTL);
	cmd_ctl.s.forceclk = 1;
	zip_reg_write(cmd_ctl.u_reg64 & 0xFF, (zip->reg_base + ZIP_CMD_CTL));

	zip_msg("ZIP_CMD_CTL  : 0x%016llx",
		zip_reg_read(zip->reg_base + ZIP_CMD_CTL));

	constants.u_reg64 = zip_reg_read(zip->reg_base + ZIP_CONSTANTS);
	zip->depth    = constants.s.depth;
	zip->onfsize  = constants.s.onfsize;
	zip->ctxsize  = constants.s.ctxsize;

	zip_msg("depth: 0x%016llx , onfsize : 0x%016llx , ctxsize : 0x%016llx",
		zip->depth, zip->onfsize, zip->ctxsize);

	/*
	 * Program ZIP_QUE(0..7)_SBUF_ADDR and ZIP_QUE(0..7)_SBUF_CTL to
	 * have the correct buffer pointer and size configured for each
	 * instruction queue.
	 */
	for (q = 0; q < ZIP_NUM_QUEUES; q++) {
		que_sbuf_ctl.u_reg64 = 0ull;
		que_sbuf_ctl.s.size = (ZIP_CMD_QBUF_SIZE / sizeof(u64));
		que_sbuf_ctl.s.inst_be   = 0;
		que_sbuf_ctl.s.stream_id = 0;
		zip_reg_write(que_sbuf_ctl.u_reg64,
			      (zip->reg_base + ZIP_QUEX_SBUF_CTL(q)));

		zip_msg("QUEX_SBUF_CTL[%d]: 0x%016llx", q,
			zip_reg_read(zip->reg_base + ZIP_QUEX_SBUF_CTL(q)));
	}

	for (q = 0; q < ZIP_NUM_QUEUES; q++) {
		memset(&zip->iq[q], 0x0, sizeof(struct zip_iq));

		spin_lock_init(&zip->iq[q].lock);

		if (zip_cmd_qbuf_alloc(zip, q)) {
			while (q != 0) {
				q--;
				zip_cmd_qbuf_free(zip, q);
			}
			return -ENOMEM;
		}

		/* Initialize tail ptr to head */
		zip->iq[q].sw_tail = zip->iq[q].sw_head;
		zip->iq[q].hw_tail = zip->iq[q].sw_head;

		/* Write the physical addr to register */
		que_sbuf_addr.u_reg64   = 0ull;
		que_sbuf_addr.s.ptr = (__pa(zip->iq[q].sw_head) >>
				       ZIP_128B_ALIGN);

		zip_msg("QUE[%d]_PTR(PHYS): 0x%016llx", q,
			(u64)que_sbuf_addr.s.ptr);

		zip_reg_write(que_sbuf_addr.u_reg64,
			      (zip->reg_base + ZIP_QUEX_SBUF_ADDR(q)));

		zip_msg("QUEX_SBUF_ADDR[%d]: 0x%016llx", q,
			zip_reg_read(zip->reg_base + ZIP_QUEX_SBUF_ADDR(q)));

		zip_dbg("sw_head :0x%lx sw_tail :0x%lx hw_tail :0x%lx",
			zip->iq[q].sw_head, zip->iq[q].sw_tail,
			zip->iq[q].hw_tail);
		zip_dbg("sw_head phy addr : 0x%lx", que_sbuf_addr.s.ptr);
	}

	/*
	 * Queue-to-ZIP core mapping
	 * If a queue is not mapped to a particular core, it is equivalent to
	 * the ZIP core being disabled.
	 */
	que_ena.u_reg64 = 0x0ull;
	/* Enabling queues based on ZIP_NUM_QUEUES */
	for (q = 0; q < ZIP_NUM_QUEUES; q++)
		que_ena.s.ena |= (0x1 << q);
	zip_reg_write(que_ena.u_reg64, (zip->reg_base + ZIP_QUE_ENA));

	zip_msg("QUE_ENA      : 0x%016llx",
		zip_reg_read(zip->reg_base + ZIP_QUE_ENA));

	for (q = 0; q < ZIP_NUM_QUEUES; q++) {
		que_map.u_reg64 = 0ull;
		/* Mapping each queue to two ZIP cores */
		que_map.s.zce = 0x3;
		zip_reg_write(que_map.u_reg64,
			      (zip->reg_base + ZIP_QUEX_MAP(q)));

		zip_msg("QUE_MAP(%d)   : 0x%016llx", q,
			zip_reg_read(zip->reg_base + ZIP_QUEX_MAP(q)));
	}

	que_pri.u_reg64 = 0ull;
	for (q = 0; q < ZIP_NUM_QUEUES; q++)
		que_pri.s.pri |= (0x1 << q); /* Higher Priority RR */
	zip_reg_write(que_pri.u_reg64, (zip->reg_base + ZIP_QUE_PRI));

	zip_msg("QUE_PRI %016llx", zip_reg_read(zip->reg_base + ZIP_QUE_PRI));

	return 0;
}
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
typedef  int uint64_t ;
struct sq_hdr_subdesc {scalar_t__ subdesc_type; int subdesc_cnt; } ;
struct snd_queue {int head; struct snd_buff* snd_buff; int /*<<< orphan*/  snd_buff_dmat; } ;
struct snd_buff {int /*<<< orphan*/ * mbuf; int /*<<< orphan*/  dmap; } ;
struct nicvf {int dummy; } ;

/* Variables and functions */
 scalar_t__ GET_SQ_DESC (struct snd_queue*,int) ; 
 int /*<<< orphan*/  NICVF_TX_LOCK (struct snd_queue*) ; 
 int /*<<< orphan*/  NICVF_TX_UNLOCK (struct snd_queue*) ; 
 int /*<<< orphan*/  NIC_QSET_SQ_0_7_HEAD ; 
 scalar_t__ SQ_DESC_TYPE_HEADER ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nicvf_put_sq_desc (struct snd_queue*,int) ; 
 int nicvf_queue_reg_read (struct nicvf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nicvf_sq_free_used_descs(struct nicvf *nic, struct snd_queue *sq, int qidx)
{
	uint64_t head;
	struct snd_buff *snd_buff;
	struct sq_hdr_subdesc *hdr;

	NICVF_TX_LOCK(sq);
	head = nicvf_queue_reg_read(nic, NIC_QSET_SQ_0_7_HEAD, qidx) >> 4;
	while (sq->head != head) {
		hdr = (struct sq_hdr_subdesc *)GET_SQ_DESC(sq, sq->head);
		if (hdr->subdesc_type != SQ_DESC_TYPE_HEADER) {
			nicvf_put_sq_desc(sq, 1);
			continue;
		}
		snd_buff = &sq->snd_buff[sq->head];
		if (snd_buff->mbuf != NULL) {
			bus_dmamap_unload(sq->snd_buff_dmat, snd_buff->dmap);
			m_freem(snd_buff->mbuf);
			sq->snd_buff[sq->head].mbuf = NULL;
		}
		nicvf_put_sq_desc(sq, hdr->subdesc_cnt + 1);
	}
	NICVF_TX_UNLOCK(sq);
}
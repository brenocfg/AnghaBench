#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ses_iterator {int global_element_index; int /*<<< orphan*/  type_index; } ;
struct ses_control_page_hdr {int control_flags; } ;
struct ses_comstat {int dummy; } ;
struct TYPE_10__ {int comstatus; int /*<<< orphan*/ * comstat; } ;
struct TYPE_8__ {int elm_idx; TYPE_6__ elm_stat; } ;
typedef  TYPE_1__ ses_control_request_t ;
struct TYPE_9__ {int /*<<< orphan*/  enc_cache; } ;
typedef  TYPE_2__ enc_softc_t ;
typedef  int /*<<< orphan*/  enc_element_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ENC_DLOG (TYPE_2__*,char*,int,...) ; 
 int ENXIO ; 
 int /*<<< orphan*/  SES_ELEM_INDEX_GLOBAL ; 
 int SES_SET_STATUS_MASK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_6__*,int) ; 
 int /*<<< orphan*/  ses_iter_init (TYPE_2__*,int /*<<< orphan*/ *,struct ses_iterator*) ; 
 int /*<<< orphan*/ * ses_iter_seek_to (struct ses_iterator*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ses_encode(enc_softc_t *enc, uint8_t *buf, int amt, ses_control_request_t *req)
{
	struct ses_iterator iter;
	enc_element_t *element;
	int offset;
	struct ses_control_page_hdr *hdr;

	ses_iter_init(enc, &enc->enc_cache, &iter);
	hdr = (struct ses_control_page_hdr *)buf;
	if (req->elm_idx == -1) {
		/* for enclosure status, at least 2 bytes are needed */
		if (amt < 2)
			return EIO;
		hdr->control_flags =
		    req->elm_stat.comstatus & SES_SET_STATUS_MASK;
		ENC_DLOG(enc, "Set EncStat %x\n", hdr->control_flags);
		return (0);
	}

	element = ses_iter_seek_to(&iter, req->elm_idx, SES_ELEM_INDEX_GLOBAL);
	if (element == NULL)
		return (ENXIO);

	/*
	 * Seek to the type set that corresponds to the requested object.
	 * The +1 is for the overall status element for the type.
	 */
	offset = sizeof(struct ses_control_page_hdr)
	       + (iter.global_element_index * sizeof(struct ses_comstat));

	/* Check for buffer overflow. */
	if (offset + sizeof(struct ses_comstat) > amt)
		return (EIO);

	/* Set the status. */
	memcpy(&buf[offset], &req->elm_stat, sizeof(struct ses_comstat));

	ENC_DLOG(enc, "Set Type 0x%x Obj 0x%x (offset %d) with %x %x %x %x\n",
	    iter.type_index, iter.global_element_index, offset,
	    req->elm_stat.comstatus, req->elm_stat.comstat[0],
	    req->elm_stat.comstat[1], req->elm_stat.comstat[2]);

	return (0);
}
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
struct ctl_sg_entry {int len; struct ctl_sg_entry* addr; } ;
typedef  struct ctl_sg_entry uint8_t ;
struct TYPE_2__ {int flags; int port_status; } ;
struct ctl_scsiio {int ext_data_filled; int kern_data_len; int ext_sg_entries; int ext_data_len; int kern_sg_entries; scalar_t__ kern_data_resid; TYPE_1__ io_hdr; struct ctl_sg_entry* kern_data_ptr; struct ctl_sg_entry* ext_data_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int CTL_FLAG_BUS_ADDR ; 
 int CTL_FLAG_DATA_IN ; 
 int CTL_FLAG_DATA_MASK ; 
 int CTL_FLAG_NO_DATAMOVE ; 
 int CTL_RETVAL_COMPLETE ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  M_CTL ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct ctl_sg_entry* bus_to_virt (struct ctl_sg_entry*) ; 
 scalar_t__ copyin (struct ctl_sg_entry*,struct ctl_sg_entry*,int) ; 
 scalar_t__ copyout (struct ctl_sg_entry*,struct ctl_sg_entry*,int) ; 
 int /*<<< orphan*/  free (struct ctl_sg_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
ctl_ioctl_do_datamove(struct ctl_scsiio *ctsio)
{
	struct ctl_sg_entry *ext_sglist, *kern_sglist;
	struct ctl_sg_entry ext_entry, kern_entry;
	int ext_sglen, ext_sg_entries, kern_sg_entries;
	int ext_sg_start, ext_offset;
	int len_to_copy;
	int kern_watermark, ext_watermark;
	int ext_sglist_malloced;
	int i, j;

	CTL_DEBUG_PRINT(("ctl_ioctl_do_datamove\n"));

	/*
	 * If this flag is set, fake the data transfer.
	 */
	if (ctsio->io_hdr.flags & CTL_FLAG_NO_DATAMOVE) {
		ext_sglist_malloced = 0;
		ctsio->ext_data_filled += ctsio->kern_data_len;
		ctsio->kern_data_resid = 0;
		goto bailout;
	}

	/*
	 * To simplify things here, if we have a single buffer, stick it in
	 * a S/G entry and just make it a single entry S/G list.
	 */
	if (ctsio->ext_sg_entries > 0) {
		int len_seen;

		ext_sglen = ctsio->ext_sg_entries * sizeof(*ext_sglist);
		ext_sglist = (struct ctl_sg_entry *)malloc(ext_sglen, M_CTL,
							   M_WAITOK);
		ext_sglist_malloced = 1;
		if (copyin(ctsio->ext_data_ptr, ext_sglist, ext_sglen) != 0) {
			ctsio->io_hdr.port_status = 31343;
			goto bailout;
		}
		ext_sg_entries = ctsio->ext_sg_entries;
		ext_sg_start = ext_sg_entries;
		ext_offset = 0;
		len_seen = 0;
		for (i = 0; i < ext_sg_entries; i++) {
			if ((len_seen + ext_sglist[i].len) >=
			     ctsio->ext_data_filled) {
				ext_sg_start = i;
				ext_offset = ctsio->ext_data_filled - len_seen;
				break;
			}
			len_seen += ext_sglist[i].len;
		}
	} else {
		ext_sglist = &ext_entry;
		ext_sglist_malloced = 0;
		ext_sglist->addr = ctsio->ext_data_ptr;
		ext_sglist->len = ctsio->ext_data_len;
		ext_sg_entries = 1;
		ext_sg_start = 0;
		ext_offset = ctsio->ext_data_filled;
	}

	if (ctsio->kern_sg_entries > 0) {
		kern_sglist = (struct ctl_sg_entry *)ctsio->kern_data_ptr;
		kern_sg_entries = ctsio->kern_sg_entries;
	} else {
		kern_sglist = &kern_entry;
		kern_sglist->addr = ctsio->kern_data_ptr;
		kern_sglist->len = ctsio->kern_data_len;
		kern_sg_entries = 1;
	}

	kern_watermark = 0;
	ext_watermark = ext_offset;
	for (i = ext_sg_start, j = 0;
	     i < ext_sg_entries && j < kern_sg_entries;) {
		uint8_t *ext_ptr, *kern_ptr;

		len_to_copy = MIN(ext_sglist[i].len - ext_watermark,
				  kern_sglist[j].len - kern_watermark);

		ext_ptr = (uint8_t *)ext_sglist[i].addr;
		ext_ptr = ext_ptr + ext_watermark;
		if (ctsio->io_hdr.flags & CTL_FLAG_BUS_ADDR) {
			/*
			 * XXX KDM fix this!
			 */
			panic("need to implement bus address support");
#if 0
			kern_ptr = bus_to_virt(kern_sglist[j].addr);
#endif
		} else
			kern_ptr = (uint8_t *)kern_sglist[j].addr;
		kern_ptr = kern_ptr + kern_watermark;

		if ((ctsio->io_hdr.flags & CTL_FLAG_DATA_MASK) ==
		     CTL_FLAG_DATA_IN) {
			CTL_DEBUG_PRINT(("ctl_ioctl_do_datamove: copying %d "
					 "bytes to user\n", len_to_copy));
			CTL_DEBUG_PRINT(("ctl_ioctl_do_datamove: from %p "
					 "to %p\n", kern_ptr, ext_ptr));
			if (copyout(kern_ptr, ext_ptr, len_to_copy) != 0) {
				ctsio->io_hdr.port_status = 31344;
				goto bailout;
			}
		} else {
			CTL_DEBUG_PRINT(("ctl_ioctl_do_datamove: copying %d "
					 "bytes from user\n", len_to_copy));
			CTL_DEBUG_PRINT(("ctl_ioctl_do_datamove: from %p "
					 "to %p\n", ext_ptr, kern_ptr));
			if (copyin(ext_ptr, kern_ptr, len_to_copy)!= 0){
				ctsio->io_hdr.port_status = 31345;
				goto bailout;
			}
		}

		ctsio->ext_data_filled += len_to_copy;
		ctsio->kern_data_resid -= len_to_copy;

		ext_watermark += len_to_copy;
		if (ext_sglist[i].len == ext_watermark) {
			i++;
			ext_watermark = 0;
		}

		kern_watermark += len_to_copy;
		if (kern_sglist[j].len == kern_watermark) {
			j++;
			kern_watermark = 0;
		}
	}

	CTL_DEBUG_PRINT(("ctl_ioctl_do_datamove: ext_sg_entries: %d, "
			 "kern_sg_entries: %d\n", ext_sg_entries,
			 kern_sg_entries));
	CTL_DEBUG_PRINT(("ctl_ioctl_do_datamove: ext_data_len = %d, "
			 "kern_data_len = %d\n", ctsio->ext_data_len,
			 ctsio->kern_data_len));

bailout:
	if (ext_sglist_malloced != 0)
		free(ext_sglist, M_CTL);

	return (CTL_RETVAL_COMPLETE);
}
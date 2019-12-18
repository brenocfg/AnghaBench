#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* fw; } ;
struct bwn_fw {TYPE_2__ initvals_band; TYPE_2__ initvals; } ;
struct bwn_mac {struct bwn_fw mac_fw; } ;
struct bwn_fwhdr {int /*<<< orphan*/  size; } ;
struct TYPE_3__ {scalar_t__ datasize; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GETFWOFFSET (TYPE_2__,size_t const) ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int bwn_fwinitvals_write (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
bwn_fw_loadinitvals(struct bwn_mac *mac)
{
#define	GETFWOFFSET(fwp, offset)				\
	((const struct bwn_fwinitvals *)((const char *)fwp.fw->data + offset))
	const size_t hdr_len = sizeof(struct bwn_fwhdr);
	const struct bwn_fwhdr *hdr;
	struct bwn_fw *fw = &mac->mac_fw;
	int error;

	hdr = (const struct bwn_fwhdr *)(fw->initvals.fw->data);
	error = bwn_fwinitvals_write(mac, GETFWOFFSET(fw->initvals, hdr_len),
	    be32toh(hdr->size), fw->initvals.fw->datasize - hdr_len);
	if (error)
		return (error);
	if (fw->initvals_band.fw) {
		hdr = (const struct bwn_fwhdr *)(fw->initvals_band.fw->data);
		error = bwn_fwinitvals_write(mac,
		    GETFWOFFSET(fw->initvals_band, hdr_len),
		    be32toh(hdr->size),
		    fw->initvals_band.fw->datasize - hdr_len);
	}
	return (error);
#undef GETFWOFFSET
}
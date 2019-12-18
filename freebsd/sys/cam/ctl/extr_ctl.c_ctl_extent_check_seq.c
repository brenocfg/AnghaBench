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
struct TYPE_2__ {int flags; } ;
union ctl_io {TYPE_1__ io_hdr; } ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  ctl_action ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_ACTION_BLOCK ; 
 int /*<<< orphan*/  CTL_ACTION_ERROR ; 
 int /*<<< orphan*/  CTL_ACTION_PASS ; 
 int CTL_FLAG_SERSEQ_DONE ; 
 scalar_t__ ctl_get_lba_len (union ctl_io*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static ctl_action
ctl_extent_check_seq(union ctl_io *io1, union ctl_io *io2)
{
	uint64_t lba1, lba2;
	uint64_t len1, len2;

	if (io1->io_hdr.flags & CTL_FLAG_SERSEQ_DONE)
		return (CTL_ACTION_PASS);
	if (ctl_get_lba_len(io1, &lba1, &len1) != 0)
		return (CTL_ACTION_ERROR);
	if (ctl_get_lba_len(io2, &lba2, &len2) != 0)
		return (CTL_ACTION_ERROR);

	if (lba1 + len1 == lba2)
		return (CTL_ACTION_BLOCK);
	return (CTL_ACTION_PASS);
}
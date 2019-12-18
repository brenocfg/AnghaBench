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
union mfi_evt {int /*<<< orphan*/  word; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct mfi_evt_list {int dummy; } ;
struct mfi_evt_detail {int dummy; } ;
typedef  int /*<<< orphan*/  mbox ;

/* Variables and functions */
 int /*<<< orphan*/  MFI_DCMD_CTRL_EVENT_GET ; 
 int mfi_dcmd_command (int,int /*<<< orphan*/ ,struct mfi_evt_list*,size_t,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mfi_get_events(int fd, struct mfi_evt_list *list, int num_events,
    union mfi_evt filter, uint32_t start_seq, uint8_t *statusp)
{
	uint32_t mbox[2];
	size_t size;

	mbox[0] = start_seq;
	mbox[1] = filter.word;
	size = sizeof(struct mfi_evt_list) + sizeof(struct mfi_evt_detail) *
	    (num_events - 1);
	return (mfi_dcmd_command(fd, MFI_DCMD_CTRL_EVENT_GET, list, size,
	    (uint8_t *)&mbox, sizeof(mbox), statusp));
}
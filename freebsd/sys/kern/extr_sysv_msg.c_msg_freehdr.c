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
struct msg {scalar_t__ msg_ts; size_t msg_spot; struct msg* msg_next; } ;
struct TYPE_4__ {size_t msgseg; scalar_t__ msgssz; } ;
struct TYPE_3__ {short next; } ;

/* Variables and functions */
 struct msg* free_msghdrs ; 
 short free_msgmaps ; 
 int /*<<< orphan*/  mac_sysvmsg_cleanup (struct msg*) ; 
 TYPE_2__ msginfo ; 
 TYPE_1__* msgmaps ; 
 int /*<<< orphan*/  nfree_msgmaps ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
msg_freehdr(struct msg *msghdr)
{
	while (msghdr->msg_ts > 0) {
		short next;
		if (msghdr->msg_spot < 0 || msghdr->msg_spot >= msginfo.msgseg)
			panic("msghdr->msg_spot out of range");
		next = msgmaps[msghdr->msg_spot].next;
		msgmaps[msghdr->msg_spot].next = free_msgmaps;
		free_msgmaps = msghdr->msg_spot;
		nfree_msgmaps++;
		msghdr->msg_spot = next;
		if (msghdr->msg_ts >= msginfo.msgssz)
			msghdr->msg_ts -= msginfo.msgssz;
		else
			msghdr->msg_ts = 0;
	}
	if (msghdr->msg_spot != -1)
		panic("msghdr->msg_spot != -1");
	msghdr->msg_next = free_msghdrs;
	free_msghdrs = msghdr;
#ifdef MAC
	mac_sysvmsg_cleanup(msghdr);
#endif
}
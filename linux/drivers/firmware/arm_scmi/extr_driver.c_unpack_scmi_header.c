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
typedef  int /*<<< orphan*/  u32 ;
struct scmi_msg_hdr {int /*<<< orphan*/  protocol_id; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_XTRACT_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_XTRACT_PROT_ID (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void unpack_scmi_header(u32 msg_hdr, struct scmi_msg_hdr *hdr)
{
	hdr->id = MSG_XTRACT_ID(msg_hdr);
	hdr->protocol_id = MSG_XTRACT_PROT_ID(msg_hdr);
}
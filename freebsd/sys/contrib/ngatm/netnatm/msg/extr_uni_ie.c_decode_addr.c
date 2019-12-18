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
typedef  int u_int ;
struct uni_msg {int /*<<< orphan*/  b_rptr; } ;
struct uni_addr {int plan; int type; int len; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
#define  UNI_ADDR_ATME 129 
#define  UNI_ADDR_E164 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
decode_addr(struct uni_addr *addr, u_int ielen, struct uni_msg *msg, u_int plan)
{
	addr->plan = plan & 0xf;
	addr->type = (plan >> 4) & 0x7;

	switch(addr->plan) {

	  case UNI_ADDR_E164:
		if(ielen > 15 || ielen == 0)
			return -1;
		addr->addr[ielen] = 0;
		break;

	  case UNI_ADDR_ATME:
		if(ielen != 20)
			return -1;
		break;

	  default:
		return -1;
	}
	(void)memcpy(addr->addr, msg->b_rptr, ielen);
	addr->len = ielen;
	msg->b_rptr += ielen;

	return 0;
}
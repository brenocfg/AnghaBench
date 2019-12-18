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
struct uni_subaddr {int type; int len; int /*<<< orphan*/  addr; } ;
struct uni_msg {int /*<<< orphan*/  b_rptr; } ;

/* Variables and functions */
#define  UNI_SUBADDR_ATME 129 
#define  UNI_SUBADDR_NSAP 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
decode_subaddr(struct uni_subaddr *addr, u_int ielen, struct uni_msg *msg,
    u_int type)
{
	switch(addr->type = (type >> 4) & 0x7) {

	  case UNI_SUBADDR_NSAP:
		if(ielen == 0 || ielen > 20)
			return -1;
		break;

	  case UNI_SUBADDR_ATME:
		if(ielen != 20)
			return -1;
		break;

	  default:
		return -1;
	}
	if(!(type & 0x80))
		return -1;
	if((type & 0x7) != 0)
		return -1;

	addr->len = ielen;
	(void)memcpy(addr->addr, msg->b_rptr, ielen);
	msg->b_rptr += ielen;

	return 0;
}
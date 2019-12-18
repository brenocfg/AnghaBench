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
struct hardware {int hlen; int /*<<< orphan*/  htype; struct ether_header* haddr; } ;
struct ether_header {unsigned char* ether_shost; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  eh ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int ETHER_HEADER_SIZE ; 
 int /*<<< orphan*/  memcpy (struct ether_header*,unsigned char*,int) ; 

ssize_t
decode_hw_header(unsigned char *buf, int bufix, struct hardware *from)
{
	struct ether_header eh;

	memcpy(&eh, buf + bufix, ETHER_HEADER_SIZE);

	memcpy(from->haddr, eh.ether_shost, sizeof(eh.ether_shost));
	from->htype = ARPHRD_ETHER;
	from->hlen = sizeof(eh.ether_shost);

	return (sizeof(eh));
}
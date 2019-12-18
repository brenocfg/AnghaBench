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
struct msg_hdr {int version; int len; } ;

/* Variables and functions */
 int _recv (int,char*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static int msg_recv_hdr(int rs, struct msg_hdr *hdr)
{
	int ret;

	ret = _recv(rs, (char *) hdr, sizeof *hdr);
	if (ret != sizeof *hdr)
		return -1;

	if (hdr->version || hdr->len < sizeof *hdr) {
		printf("invalid version %d or length %d\n",
		       hdr->version, hdr->len);
		return -1;
	}

	return sizeof *hdr;
}
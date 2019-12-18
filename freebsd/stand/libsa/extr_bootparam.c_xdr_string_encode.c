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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  htonl (int) ; 

int
xdr_string_encode(char **pkt, char *str, int len)
{
	uint32_t *lenp;
	char *datap;
	int padlen = (len + 3) & ~3;	/* padded length */

	/* The data will be int aligned. */
	lenp = (uint32_t *) *pkt;
	*pkt += sizeof(*lenp);
	*lenp = htonl(len);

	datap = *pkt;
	*pkt += padlen;
	bcopy(str, datap, len);

	return (0);
}
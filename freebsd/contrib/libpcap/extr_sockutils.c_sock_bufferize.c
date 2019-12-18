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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int,char*) ; 

int sock_bufferize(const char *buffer, int size, char *tempbuf, int *offset, int totsize, int checkonly, char *errbuf, int errbuflen)
{
	if ((*offset + size) > totsize)
	{
		if (errbuf)
			pcap_snprintf(errbuf, errbuflen, "Not enough space in the temporary send buffer.");
		return -1;
	}

	if (!checkonly)
		memcpy(tempbuf + (*offset), buffer, size);

	(*offset) += size;

	return 0;
}
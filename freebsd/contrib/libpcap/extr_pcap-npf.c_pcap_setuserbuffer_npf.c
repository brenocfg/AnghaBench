#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* buffer; int bufsize; int /*<<< orphan*/  errbuf; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
pcap_setuserbuffer_npf(pcap_t *p, int size)
{
	unsigned char *new_buff;

	if (size<=0) {
		/* Bogus parameter */
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "Error: invalid size %d",size);
		return (-1);
	}

	/* Allocate the buffer */
	new_buff=(unsigned char*)malloc(sizeof(char)*size);

	if (!new_buff) {
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "Error: not enough memory");
		return (-1);
	}

	free(p->buffer);

	p->buffer=new_buff;
	p->bufsize=size;

	return (0);
}
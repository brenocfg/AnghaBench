#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* getnonblock_op ) (TYPE_1__*) ;int /*<<< orphan*/  errbuf; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*) ; 

int
pcap_getnonblock(pcap_t *p, char *errbuf)
{
	int ret;

	ret = p->getnonblock_op(p);
	if (ret == -1) {
		/*
		 * The get nonblock operation sets p->errbuf; this
		 * function *shouldn't* have had a separate errbuf
		 * argument, as it didn't need one, but I goofed
		 * when adding it.
		 *
		 * We copy the error message to errbuf, so callers
		 * can find it in either place.
		 */
		strlcpy(errbuf, p->errbuf, PCAP_ERRBUF_SIZE);
	}
	return (ret);
}
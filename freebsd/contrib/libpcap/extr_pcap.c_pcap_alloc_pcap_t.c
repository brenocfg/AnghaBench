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
struct TYPE_3__ {int fd; int selectable_fd; int /*<<< orphan*/ * priv; int /*<<< orphan*/ * required_select_timeout; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  errno ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static pcap_t *
pcap_alloc_pcap_t(char *ebuf, size_t size)
{
	char *chunk;
	pcap_t *p;

	/*
	 * Allocate a chunk of memory big enough for a pcap_t
	 * plus a structure following it of size "size".  The
	 * structure following it is a private data structure
	 * for the routines that handle this pcap_t.
	 */
	chunk = malloc(sizeof (pcap_t) + size);
	if (chunk == NULL) {
		pcap_fmt_errmsg_for_errno(ebuf, PCAP_ERRBUF_SIZE,
		    errno, "malloc");
		return (NULL);
	}
	memset(chunk, 0, sizeof (pcap_t) + size);

	/*
	 * Get a pointer to the pcap_t at the beginning.
	 */
	p = (pcap_t *)chunk;

#ifdef _WIN32
	p->handle = INVALID_HANDLE_VALUE;	/* not opened yet */
#else /* _WIN32 */
	p->fd = -1;	/* not opened yet */
#ifndef MSDOS
	p->selectable_fd = -1;
	p->required_select_timeout = NULL;
#endif /* MSDOS */
#endif /* _WIN32 */

	if (size == 0) {
		/* No private data was requested. */
		p->priv = NULL;
	} else {
		/*
		 * Set the pointer to the private data; that's the structure
		 * of size "size" following the pcap_t.
		 */
		p->priv = (void *)(chunk + sizeof (pcap_t));
	}

	return (p);
}
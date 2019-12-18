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
struct nm_pcap_file {int /*<<< orphan*/  fd; int /*<<< orphan*/  filesize; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct nm_pcap_file*,int) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct nm_pcap_file*) ; 
 int /*<<< orphan*/  munmap (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_pcap(struct nm_pcap_file *pf)
{
    if (!pf)
	return;

    munmap((void *)(uintptr_t)pf->data, pf->filesize);
    close(pf->fd);
    bzero(pf, sizeof(*pf));
    free(pf);
    return;
}
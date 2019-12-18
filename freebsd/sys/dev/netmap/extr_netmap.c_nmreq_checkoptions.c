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
struct nmreq_option {scalar_t__ nro_status; scalar_t__ nro_next; } ;
struct nmreq_header {scalar_t__ nr_options; } ;

/* Variables and functions */
 scalar_t__ EOPNOTSUPP ; 

__attribute__((used)) static int
nmreq_checkoptions(struct nmreq_header *hdr)
{
	struct nmreq_option *opt;
	/* return error if there is still any option
	 * marked as not supported
	 */

	for (opt = (struct nmreq_option *)(uintptr_t)hdr->nr_options; opt;
	     opt = (struct nmreq_option *)(uintptr_t)opt->nro_next)
		if (opt->nro_status == EOPNOTSUPP)
			return EOPNOTSUPP;

	return 0;
}
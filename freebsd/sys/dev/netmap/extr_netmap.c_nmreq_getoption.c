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
typedef  size_t uint16_t ;
struct nmreq_option {int dummy; } ;
struct nmreq_header {scalar_t__ nr_options; } ;

/* Variables and functions */
 struct nmreq_option** NETMAP_REQ_OPT_MAX ; 

struct nmreq_option *
nmreq_getoption(struct nmreq_header *hdr, uint16_t reqtype)
{
	struct nmreq_option **opt_tab;

	if (!hdr->nr_options)
		return NULL;

	opt_tab = (struct nmreq_option **)((uintptr_t)hdr->nr_options) -
	    (NETMAP_REQ_OPT_MAX + 1);
	return opt_tab[reqtype];
}
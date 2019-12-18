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
struct wpabuf {int dummy; } ;
struct p2p_data {struct wpabuf** vendor_elem; } ;

/* Variables and functions */

void p2p_set_vendor_elems(struct p2p_data *p2p, struct wpabuf **vendor_elem)
{
	p2p->vendor_elem = vendor_elem;
}
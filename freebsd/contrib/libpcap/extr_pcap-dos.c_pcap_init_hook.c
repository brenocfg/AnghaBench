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
 scalar_t__ _w32__bootp_on ; 
 scalar_t__ _w32__dhcp_on ; 
 scalar_t__ _w32__do_mask_req ; 
 scalar_t__ _w32__rarp_on ; 
 scalar_t__ _w32_dynamic_host ; 
 int /*<<< orphan*/  prev_post_hook () ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void pcap_init_hook (void)
{
  _w32__bootp_on = _w32__dhcp_on = _w32__rarp_on = 0;
  _w32__do_mask_req = 0;
  _w32_dynamic_host = 0;
  if (prev_post_hook)
    (*prev_post_hook)();
}
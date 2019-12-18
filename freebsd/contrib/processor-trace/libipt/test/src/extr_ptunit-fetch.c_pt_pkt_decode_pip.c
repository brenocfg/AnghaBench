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
struct pt_packet_decoder {int dummy; } ;
struct pt_packet {int dummy; } ;

/* Variables and functions */
 int pte_internal ; 

int pt_pkt_decode_pip(struct pt_packet_decoder *d, struct pt_packet *p)
{
	(void) d;
	(void) p;

	return -pte_internal;
}
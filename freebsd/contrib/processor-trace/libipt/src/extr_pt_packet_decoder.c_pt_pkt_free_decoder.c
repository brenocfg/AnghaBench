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

/* Variables and functions */
 int /*<<< orphan*/  free (struct pt_packet_decoder*) ; 
 int /*<<< orphan*/  pt_pkt_decoder_fini (struct pt_packet_decoder*) ; 

void pt_pkt_free_decoder(struct pt_packet_decoder *decoder)
{
	pt_pkt_decoder_fini(decoder);
	free(decoder);
}
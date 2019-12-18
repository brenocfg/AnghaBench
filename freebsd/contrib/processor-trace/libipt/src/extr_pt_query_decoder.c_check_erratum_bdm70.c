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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct pt_packet_decoder {int dummy; } ;
struct pt_config {int /*<<< orphan*/  const* begin; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_pkt_decoder_fini (struct pt_packet_decoder*) ; 
 int pt_pkt_decoder_init (struct pt_packet_decoder*,struct pt_config const*) ; 
 int pt_pkt_sync_set (struct pt_packet_decoder*,int /*<<< orphan*/ ) ; 
 int pte_internal ; 
 int scan_for_erratum_bdm70 (struct pt_packet_decoder*) ; 

__attribute__((used)) static int check_erratum_bdm70(const uint8_t *pos,
			       const struct pt_config *config)
{
	struct pt_packet_decoder decoder;
	int errcode;

	if (!pos || !config)
		return -pte_internal;

	errcode = pt_pkt_decoder_init(&decoder, config);
	if (errcode < 0)
		return errcode;

	errcode = pt_pkt_sync_set(&decoder, (uint64_t) (pos - config->begin));
	if (errcode >= 0)
		errcode = scan_for_erratum_bdm70(&decoder);

	pt_pkt_decoder_fini(&decoder);
	return errcode;
}
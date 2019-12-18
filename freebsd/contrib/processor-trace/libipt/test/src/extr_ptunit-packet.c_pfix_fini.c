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
struct ptunit_result {int dummy; } ;
struct packet_fixture {int /*<<< orphan*/  decoder; int /*<<< orphan*/  encoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_encoder_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_pkt_decoder_fini (int /*<<< orphan*/ *) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result pfix_fini(struct packet_fixture *pfix)
{
	pt_encoder_fini(&pfix->encoder);
	pt_pkt_decoder_fini(&pfix->decoder);

	return ptu_passed();
}
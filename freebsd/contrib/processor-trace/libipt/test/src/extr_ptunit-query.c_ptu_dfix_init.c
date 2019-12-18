#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ptunit_result {int dummy; } ;
struct TYPE_3__ {int have_ip; scalar_t__ suppressed; int /*<<< orphan*/  ip; } ;
struct TYPE_4__ {TYPE_1__ ip; } ;
struct pt_config {scalar_t__ end; scalar_t__ begin; } ;
struct ptu_decoder_fixture {int /*<<< orphan*/  (* header ) (struct ptu_decoder_fixture*) ;TYPE_2__ decoder; TYPE_1__ last_ip; int /*<<< orphan*/  encoder; scalar_t__ buffer; struct pt_config config; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pt_config_init (struct pt_config*) ; 
 int /*<<< orphan*/  pt_dfix_bad_ip ; 
 int pt_encoder_init (int /*<<< orphan*/ *,struct pt_config*) ; 
 int pt_qry_decoder_init (TYPE_2__*,struct pt_config*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  stub1 (struct ptu_decoder_fixture*) ; 

__attribute__((used)) static struct ptunit_result ptu_dfix_init(struct ptu_decoder_fixture *dfix)
{
	struct pt_config *config = &dfix->config;
	int errcode;

	(void) memset(dfix->buffer, 0, sizeof(dfix->buffer));

	pt_config_init(config);

	config->begin = dfix->buffer;
	config->end = dfix->buffer + sizeof(dfix->buffer);

	errcode = pt_encoder_init(&dfix->encoder, config);
	ptu_int_eq(errcode, 0);

	errcode = pt_qry_decoder_init(&dfix->decoder, config);
	ptu_int_eq(errcode, 0);

	dfix->decoder.ip.ip = pt_dfix_bad_ip;
	dfix->decoder.ip.have_ip = 1;
	dfix->decoder.ip.suppressed = 0;

	dfix->last_ip = dfix->decoder.ip;

	if (dfix->header)
		dfix->header(dfix);

	return ptu_passed();
}
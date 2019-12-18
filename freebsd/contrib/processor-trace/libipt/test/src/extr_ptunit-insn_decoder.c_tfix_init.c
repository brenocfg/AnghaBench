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
struct pt_config {int /*<<< orphan*/ * end; int /*<<< orphan*/ * begin; } ;
struct test_fixture {int /*<<< orphan*/  decoder; int /*<<< orphan*/ * buffer; struct pt_config config; } ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pt_config_init (struct pt_config*) ; 
 int pt_insn_decoder_init (int /*<<< orphan*/ *,struct pt_config*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result tfix_init(struct test_fixture *tfix)
{
	struct pt_config *config;
	uint8_t *buffer;
	int errcode;

	config = &tfix->config;
	buffer = tfix->buffer;

	memset(buffer, 0, sizeof(tfix->buffer));

	pt_config_init(config);
	config->begin = buffer;
	config->end = buffer + sizeof(tfix->buffer);

	errcode = pt_insn_decoder_init(&tfix->decoder, config);
	ptu_int_eq(errcode, 0);

	return ptu_passed();
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ptunit_result {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  begin; } ;
struct pt_query_decoder {TYPE_1__ config; int /*<<< orphan*/  pos; } ;
struct ptu_decoder_fixture {struct pt_query_decoder decoder; } ;

/* Variables and functions */
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result
ptu_dfix_header_sync(struct ptu_decoder_fixture *dfix)
{
	struct pt_query_decoder *decoder = &dfix->decoder;

	/* Synchronize the decoder at the beginning of the buffer. */
	decoder->pos = decoder->config.begin;

	return ptu_passed();
}
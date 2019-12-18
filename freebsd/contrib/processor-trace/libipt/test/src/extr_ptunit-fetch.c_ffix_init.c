#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ptunit_result {int dummy; } ;
struct TYPE_3__ {int size; struct TYPE_3__* end; struct TYPE_3__* begin; } ;
struct fetch_fixture {TYPE_1__ config; int /*<<< orphan*/  encoder; TYPE_1__* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pt_encoder_init (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pt_opc_bad ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result ffix_init(struct fetch_fixture *ffix)
{
	memset(ffix->buffer, pt_opc_bad, sizeof(ffix->buffer));

	memset(&ffix->config, 0, sizeof(ffix->config));
	ffix->config.size = sizeof(ffix->config);
	ffix->config.begin = ffix->buffer;
	ffix->config.end = ffix->buffer + sizeof(ffix->buffer);

	pt_encoder_init(&ffix->encoder, &ffix->config);

	return ptu_passed();
}
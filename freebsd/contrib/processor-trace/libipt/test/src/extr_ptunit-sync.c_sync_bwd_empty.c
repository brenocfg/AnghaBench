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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  end; int /*<<< orphan*/  begin; } ;
struct sync_fixture {TYPE_1__ config; } ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 int pt_sync_backward (int /*<<< orphan*/  const**,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pte_eos ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result sync_bwd_empty(struct sync_fixture *sfix)
{
	const uint8_t *sync;
	int errcode;

	sfix->config.end = sfix->config.begin;

	errcode = pt_sync_backward(&sync, sfix->config.end, &sfix->config);
	ptu_int_eq(errcode, -pte_eos);

	return ptu_passed();
}
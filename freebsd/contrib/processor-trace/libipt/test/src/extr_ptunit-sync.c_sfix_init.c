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
struct TYPE_2__ {int size; struct TYPE_2__* end; struct TYPE_2__* begin; } ;
struct sync_fixture {TYPE_1__* buffer; TYPE_1__ config; } ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result sfix_init(struct sync_fixture *sfix)
{
	memset(sfix->buffer, 0xcd, sizeof(sfix->buffer));

	memset(&sfix->config, 0, sizeof(sfix->config));
	sfix->config.size = sizeof(sfix->config);
	sfix->config.begin = sfix->buffer;
	sfix->config.end = sfix->buffer + sizeof(sfix->buffer);

	return ptu_passed();
}
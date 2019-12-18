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
struct pt_last_ip {int /*<<< orphan*/  suppressed; int /*<<< orphan*/  have_ip; int /*<<< orphan*/  ip; } ;
typedef  int /*<<< orphan*/  last_ip ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_last_ip*,int,int) ; 
 int /*<<< orphan*/  pt_last_ip_init (struct pt_last_ip*) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static struct ptunit_result init(void)
{
	struct pt_last_ip last_ip;

	memset(&last_ip, 0xcd, sizeof(last_ip));

	pt_last_ip_init(&last_ip);

	ptu_uint_eq(last_ip.ip, 0ull);
	ptu_uint_eq(last_ip.have_ip, 0);
	ptu_uint_eq(last_ip.suppressed, 0);

	return ptu_passed();
}
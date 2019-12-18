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
struct pt_tnt_cache {int /*<<< orphan*/  index; int /*<<< orphan*/  tnt; } ;
struct pt_packet_tnt {unsigned long long bit_size; unsigned long long payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_tnt_cache_init (struct pt_tnt_cache*) ; 
 int pt_tnt_cache_update_tnt (struct pt_tnt_cache*,struct pt_packet_tnt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static struct ptunit_result update_tnt(void)
{
	struct pt_tnt_cache tnt_cache;
	struct pt_packet_tnt packet;
	int errcode;

	pt_tnt_cache_init(&tnt_cache);

	packet.bit_size = 4ull;
	packet.payload = 8ull;

	errcode = pt_tnt_cache_update_tnt(&tnt_cache, &packet, NULL);
	ptu_int_eq(errcode, 0);
	ptu_uint_eq(tnt_cache.tnt, 8ull);
	ptu_uint_eq(tnt_cache.index, 1ull << 3);

	return ptu_passed();
}
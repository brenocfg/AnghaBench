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
struct ptunit_result {int dummy; } ;
struct pt_packet {int dummy; } ;

/* Variables and functions */
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (struct pt_packet const*) ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static struct ptunit_result ptu_pkt_eq(const struct pt_packet *enc,
				       const struct pt_packet *dec)
{
	const uint8_t *renc, *rdec;
	size_t byte;

	ptu_ptr(enc);
	ptu_ptr(dec);

	renc = (const uint8_t *) enc;
	rdec = (const uint8_t *) dec;

	for (byte = 0; byte < sizeof(*enc); ++byte)
		ptu_uint_eq(renc[byte], rdec[byte]);

	return ptu_passed();
}
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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct mgmt_body_t {size_t reason_code; } ;
typedef  int /*<<< orphan*/  pbody ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 size_t EXTRACT_LE_16BITS (int /*<<< orphan*/  const*) ; 
 scalar_t__ IEEE802_11_REASON_LEN ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TTEST2 (int /*<<< orphan*/  const,scalar_t__) ; 
 size_t NUM_REASONS ; 
 int /*<<< orphan*/  memset (struct mgmt_body_t*,int /*<<< orphan*/ ,int) ; 
 char** reason_text ; 

__attribute__((used)) static int
handle_disassoc(netdissect_options *ndo,
                const u_char *p, u_int length)
{
	struct mgmt_body_t  pbody;

	memset(&pbody, 0, sizeof(pbody));

	if (!ND_TTEST2(*p, IEEE802_11_REASON_LEN))
		return 0;
	if (length < IEEE802_11_REASON_LEN)
		return 0;
	pbody.reason_code = EXTRACT_LE_16BITS(p);

	ND_PRINT((ndo, ": %s",
	    (pbody.reason_code < NUM_REASONS)
		? reason_text[pbody.reason_code]
		: "Reserved"));

	return 1;
}
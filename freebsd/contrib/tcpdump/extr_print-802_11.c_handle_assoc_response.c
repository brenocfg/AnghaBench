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
typedef  int uint16_t ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct mgmt_body_t {size_t status_code; int aid; void* capability_info; } ;
typedef  int /*<<< orphan*/  pbody ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ CAPABILITY_PRIVACY (void*) ; 
 void* EXTRACT_LE_16BITS (int /*<<< orphan*/  const*) ; 
 scalar_t__ IEEE802_11_AID_LEN ; 
 scalar_t__ IEEE802_11_CAPINFO_LEN ; 
 scalar_t__ IEEE802_11_STATUS_LEN ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TTEST2 (int /*<<< orphan*/  const,scalar_t__) ; 
 size_t NUM_STATUSES ; 
 int /*<<< orphan*/  memset (struct mgmt_body_t*,int /*<<< orphan*/ ,int) ; 
 int parse_elements (int /*<<< orphan*/ *,struct mgmt_body_t*,int /*<<< orphan*/  const*,int,scalar_t__) ; 
 char** status_text ; 

__attribute__((used)) static int
handle_assoc_response(netdissect_options *ndo,
                      const u_char *p, u_int length)
{
	struct mgmt_body_t pbody;
	int offset = 0;
	int ret;

	memset(&pbody, 0, sizeof(pbody));

	if (!ND_TTEST2(*p, IEEE802_11_CAPINFO_LEN + IEEE802_11_STATUS_LEN +
	    IEEE802_11_AID_LEN))
		return 0;
	if (length < IEEE802_11_CAPINFO_LEN + IEEE802_11_STATUS_LEN +
	    IEEE802_11_AID_LEN)
		return 0;
	pbody.capability_info = EXTRACT_LE_16BITS(p);
	offset += IEEE802_11_CAPINFO_LEN;
	length -= IEEE802_11_CAPINFO_LEN;
	pbody.status_code = EXTRACT_LE_16BITS(p+offset);
	offset += IEEE802_11_STATUS_LEN;
	length -= IEEE802_11_STATUS_LEN;
	pbody.aid = EXTRACT_LE_16BITS(p+offset);
	offset += IEEE802_11_AID_LEN;
	length -= IEEE802_11_AID_LEN;

	ret = parse_elements(ndo, &pbody, p, offset, length);

	ND_PRINT((ndo, " AID(%x) :%s: %s", ((uint16_t)(pbody.aid << 2 )) >> 2 ,
	    CAPABILITY_PRIVACY(pbody.capability_info) ? " PRIVACY " : "",
	    (pbody.status_code < NUM_STATUSES
		? status_text[pbody.status_code]
		: "n/a")));

	return ret;
}
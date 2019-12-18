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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct mgmt_body_t {int auth_alg; int auth_trans_seq_num; size_t status_code; } ;
typedef  int /*<<< orphan*/  pbody ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 void* EXTRACT_LE_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TTEST2 (int /*<<< orphan*/  const,int) ; 
 int NUM_AUTH_ALGS ; 
 size_t NUM_STATUSES ; 
 char** auth_alg_text ; 
 int /*<<< orphan*/  memset (struct mgmt_body_t*,int /*<<< orphan*/ ,int) ; 
 int parse_elements (int /*<<< orphan*/ *,struct mgmt_body_t*,int /*<<< orphan*/  const*,int,int) ; 
 char** status_text ; 

__attribute__((used)) static int
handle_auth(netdissect_options *ndo,
            const u_char *p, u_int length)
{
	struct mgmt_body_t  pbody;
	int offset = 0;
	int ret;

	memset(&pbody, 0, sizeof(pbody));

	if (!ND_TTEST2(*p, 6))
		return 0;
	if (length < 6)
		return 0;
	pbody.auth_alg = EXTRACT_LE_16BITS(p);
	offset += 2;
	length -= 2;
	pbody.auth_trans_seq_num = EXTRACT_LE_16BITS(p + offset);
	offset += 2;
	length -= 2;
	pbody.status_code = EXTRACT_LE_16BITS(p + offset);
	offset += 2;
	length -= 2;

	ret = parse_elements(ndo, &pbody, p, offset, length);

	if ((pbody.auth_alg == 1) &&
	    ((pbody.auth_trans_seq_num == 2) ||
	     (pbody.auth_trans_seq_num == 3))) {
		ND_PRINT((ndo, " (%s)-%x [Challenge Text] %s",
		    (pbody.auth_alg < NUM_AUTH_ALGS)
			? auth_alg_text[pbody.auth_alg]
			: "Reserved",
		    pbody.auth_trans_seq_num,
		    ((pbody.auth_trans_seq_num % 2)
		        ? ((pbody.status_code < NUM_STATUSES)
			       ? status_text[pbody.status_code]
			       : "n/a") : "")));
		return ret;
	}
	ND_PRINT((ndo, " (%s)-%x: %s",
	    (pbody.auth_alg < NUM_AUTH_ALGS)
		? auth_alg_text[pbody.auth_alg]
		: "Reserved",
	    pbody.auth_trans_seq_num,
	    (pbody.auth_trans_seq_num % 2)
	        ? ((pbody.status_code < NUM_STATUSES)
		    ? status_text[pbody.status_code]
	            : "n/a")
	        : ""));

	return ret;
}
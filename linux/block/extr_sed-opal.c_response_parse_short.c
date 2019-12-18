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
typedef  int u8 ;
typedef  int u64 ;
struct TYPE_2__ {int u; } ;
struct opal_resp_tok {int const* pos; int len; TYPE_1__ stored; int /*<<< orphan*/  type; int /*<<< orphan*/  width; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  OPAL_DTA_TOKENID_BYTESTRING ; 
 int /*<<< orphan*/  OPAL_DTA_TOKENID_SINT ; 
 int /*<<< orphan*/  OPAL_DTA_TOKENID_UINT ; 
 int /*<<< orphan*/  OPAL_WIDTH_SHORT ; 
 int const SHORT_ATOM_BYTESTRING ; 
 int const SHORT_ATOM_LEN_MASK ; 
 int const SHORT_ATOM_SIGNED ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static ssize_t response_parse_short(struct opal_resp_tok *tok,
				    const u8 *pos)
{
	tok->pos = pos;
	tok->len = (pos[0] & SHORT_ATOM_LEN_MASK) + 1;
	tok->width = OPAL_WIDTH_SHORT;

	if (pos[0] & SHORT_ATOM_BYTESTRING) {
		tok->type = OPAL_DTA_TOKENID_BYTESTRING;
	} else if (pos[0] & SHORT_ATOM_SIGNED) {
		tok->type = OPAL_DTA_TOKENID_SINT;
	} else {
		u64 u_integer = 0;
		ssize_t i, b = 0;

		tok->type = OPAL_DTA_TOKENID_UINT;
		if (tok->len > 9) {
			pr_debug("uint64 with more than 8 bytes\n");
			return -EINVAL;
		}
		for (i = tok->len - 1; i > 0; i--) {
			u_integer |= ((u64)pos[i] << (8 * b));
			b++;
		}
		tok->stored.u = u_integer;
	}

	return tok->len;
}
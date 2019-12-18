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
typedef  int u8 ;
struct opal_resp_tok {int const* pos; int len; int /*<<< orphan*/  type; int /*<<< orphan*/  width; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int const LONG_ATOM_BYTESTRING ; 
 int const LONG_ATOM_SIGNED ; 
 int /*<<< orphan*/  OPAL_DTA_TOKENID_BYTESTRING ; 
 int /*<<< orphan*/  OPAL_DTA_TOKENID_SINT ; 
 int /*<<< orphan*/  OPAL_DTA_TOKENID_UINT ; 
 int /*<<< orphan*/  OPAL_WIDTH_LONG ; 

__attribute__((used)) static ssize_t response_parse_long(struct opal_resp_tok *tok,
				   const u8 *pos)
{
	tok->pos = pos;
	tok->len = ((pos[1] << 16) | (pos[2] << 8) | pos[3]) + 4;
	tok->width = OPAL_WIDTH_LONG;

	if (pos[0] & LONG_ATOM_BYTESTRING)
		tok->type = OPAL_DTA_TOKENID_BYTESTRING;
	else if (pos[0] & LONG_ATOM_SIGNED)
		tok->type = OPAL_DTA_TOKENID_SINT;
	else
		tok->type = OPAL_DTA_TOKENID_UINT;

	return tok->len;
}
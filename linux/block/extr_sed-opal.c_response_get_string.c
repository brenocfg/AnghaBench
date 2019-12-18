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
struct parsed_resp {int dummy; } ;
struct opal_resp_tok {scalar_t__ type; int width; char* pos; size_t len; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct opal_resp_tok const*) ; 
 scalar_t__ OPAL_DTA_TOKENID_BYTESTRING ; 
#define  OPAL_WIDTH_LONG 131 
#define  OPAL_WIDTH_MEDIUM 130 
#define  OPAL_WIDTH_SHORT 129 
#define  OPAL_WIDTH_TINY 128 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct opal_resp_tok* response_get_token (struct parsed_resp const*,int) ; 

__attribute__((used)) static size_t response_get_string(const struct parsed_resp *resp, int n,
				  const char **store)
{
	u8 skip;
	const struct opal_resp_tok *tok;

	*store = NULL;
	tok = response_get_token(resp, n);
	if (IS_ERR(tok))
		return 0;

	if (tok->type != OPAL_DTA_TOKENID_BYTESTRING) {
		pr_debug("Token is not a byte string!\n");
		return 0;
	}

	switch (tok->width) {
	case OPAL_WIDTH_TINY:
	case OPAL_WIDTH_SHORT:
		skip = 1;
		break;
	case OPAL_WIDTH_MEDIUM:
		skip = 2;
		break;
	case OPAL_WIDTH_LONG:
		skip = 4;
		break;
	default:
		pr_debug("Token has invalid width!\n");
		return 0;
	}

	*store = tok->pos + skip;

	return tok->len - skip;
}
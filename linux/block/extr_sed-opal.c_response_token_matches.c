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
typedef  scalar_t__ u8 ;
struct opal_resp_tok {scalar_t__ type; scalar_t__* pos; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct opal_resp_tok const*) ; 
 scalar_t__ OPAL_DTA_TOKENID_TOKEN ; 

__attribute__((used)) static bool response_token_matches(const struct opal_resp_tok *token, u8 match)
{
	if (IS_ERR(token) ||
	    token->type != OPAL_DTA_TOKENID_TOKEN ||
	    token->pos[0] != match)
		return false;
	return true;
}
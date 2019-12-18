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
typedef  int /*<<< orphan*/  h2o_token_t ;

/* Variables and functions */
 int /*<<< orphan*/  const* H2O_TOKEN_CONNECTION ; 
 int /*<<< orphan*/  const* H2O_TOKEN_CONTENT_LENGTH ; 
 int /*<<< orphan*/  const* H2O_TOKEN_DATE ; 
 int /*<<< orphan*/  const* H2O_TOKEN_SERVER ; 
 int /*<<< orphan*/  const* H2O_TOKEN_TRANSFER_ENCODING ; 

int h2o_headers_is_prohibited_name(const h2o_token_t *token)
{
    /* prohibit connection-specific headers */
    if (token == H2O_TOKEN_CONNECTION || token == H2O_TOKEN_CONTENT_LENGTH || token == H2O_TOKEN_TRANSFER_ENCODING)
        return 1;
    /* prohibit headers added at protocol layer */
    if (token == H2O_TOKEN_DATE || token == H2O_TOKEN_SERVER)
        return 1;
    /* all others are permitted */
    return 0;
}
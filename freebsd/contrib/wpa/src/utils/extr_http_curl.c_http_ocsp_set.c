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
struct http_ctx {int /*<<< orphan*/  ocsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANDATORY_OCSP ; 
 int /*<<< orphan*/  NO_OCSP ; 
 int /*<<< orphan*/  OPTIONAL_OCSP ; 

void http_ocsp_set(struct http_ctx *ctx, int val)
{
	if (val == 0)
		ctx->ocsp = NO_OCSP;
	else if (val == 1)
		ctx->ocsp = OPTIONAL_OCSP;
	if (val == 2)
		ctx->ocsp = MANDATORY_OCSP;
}
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
struct xml_ctx {int /*<<< orphan*/  cdata; } ;
typedef  int /*<<< orphan*/  XML_Char ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmemdupz (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void
xml_cdata(void *userData, const XML_Char *s, int len)
{
	struct xml_ctx *ctx = (struct xml_ctx *)userData;
	free(ctx->cdata);
	ctx->cdata = xmemdupz(s, len);
}
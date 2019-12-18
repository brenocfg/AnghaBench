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
typedef  int /*<<< orphan*/  MDX_CTX ;

/* Variables and functions */
 char* MDXEnd (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  MDXInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDXUpdate (int /*<<< orphan*/ *,void const*,unsigned int) ; 

char *
MDXData (const void *data, unsigned int len, char *buf)
{
	MDX_CTX ctx;

	MDXInit(&ctx);
	MDXUpdate(&ctx,data,len);
	return (MDXEnd(&ctx, buf));
}
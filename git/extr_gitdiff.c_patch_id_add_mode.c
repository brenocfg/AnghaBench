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
typedef  int /*<<< orphan*/  git_SHA_CTX ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  git_SHA1_Update (int /*<<< orphan*/ *,char*,int) ; 
 int xsnprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static void patch_id_add_mode(git_SHA_CTX *ctx, unsigned mode)
{
	/* large enough for 2^32 in octal */
	char buf[12];
	int len = xsnprintf(buf, sizeof(buf), "%06o", mode);
	git_SHA1_Update(ctx, buf, len);
}
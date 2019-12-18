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
struct stat {int st_mode; scalar_t__ st_size; } ;
struct rbcfg_ctx {scalar_t__ buflen; int /*<<< orphan*/  tmp_file; } ;

/* Variables and functions */
 int S_IFREG ; 
 int stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int
rbcfg_check_tmp(struct rbcfg_ctx *ctx)
{
	struct stat s;
	int err;

	err = stat(ctx->tmp_file, &s);
	if (err < 0)
		return 0;

	if ((s.st_mode & S_IFREG) == 0)
		return 0;

	if (s.st_size != ctx->buflen)
		return 0;

	return 1;
}
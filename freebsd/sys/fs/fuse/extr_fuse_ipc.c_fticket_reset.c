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
struct fuse_ticket {scalar_t__ tk_flag; int /*<<< orphan*/  tk_aw_type; scalar_t__ tk_aw_bufsize; int /*<<< orphan*/ * tk_aw_bufdata; scalar_t__ tk_aw_errno; int /*<<< orphan*/  tk_aw_ohead; int /*<<< orphan*/  tk_ms_type; scalar_t__ tk_ms_bufsize; int /*<<< orphan*/ * tk_ms_bufdata; } ;
struct fuse_out_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FT_A_FIOV ; 
 int /*<<< orphan*/  FT_M_FIOV ; 
 int /*<<< orphan*/  FUSE_ASSERT_AW_DONE (struct fuse_ticket*) ; 
 int /*<<< orphan*/  FUSE_ASSERT_MS_DONE (struct fuse_ticket*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
fticket_reset(struct fuse_ticket *ftick)
{
	FUSE_ASSERT_MS_DONE(ftick);
	FUSE_ASSERT_AW_DONE(ftick);

	ftick->tk_ms_bufdata = NULL;
	ftick->tk_ms_bufsize = 0;
	ftick->tk_ms_type = FT_M_FIOV;

	bzero(&ftick->tk_aw_ohead, sizeof(struct fuse_out_header));

	ftick->tk_aw_errno = 0;
	ftick->tk_aw_bufdata = NULL;
	ftick->tk_aw_bufsize = 0;
	ftick->tk_aw_type = FT_A_FIOV;

	ftick->tk_flag = 0;
}
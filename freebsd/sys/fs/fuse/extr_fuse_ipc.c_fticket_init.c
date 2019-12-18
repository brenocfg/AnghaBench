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
struct fuse_ticket {int /*<<< orphan*/  tk_aw_type; int /*<<< orphan*/  tk_aw_fiov; int /*<<< orphan*/  tk_aw_mtx; int /*<<< orphan*/  tk_ms_type; int /*<<< orphan*/  tk_ms_fiov; } ;
struct fuse_in_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FT_A_FIOV ; 
 int /*<<< orphan*/  FT_M_FIOV ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  bzero (struct fuse_ticket*,int) ; 
 int /*<<< orphan*/  fiov_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fticket_init(void *mem, int size, int flags)
{
	struct fuse_ticket *ftick = mem;

	bzero(ftick, sizeof(struct fuse_ticket));

	fiov_init(&ftick->tk_ms_fiov, sizeof(struct fuse_in_header));
	ftick->tk_ms_type = FT_M_FIOV;

	mtx_init(&ftick->tk_aw_mtx, "fuse answer delivery mutex", NULL, MTX_DEF);
	fiov_init(&ftick->tk_aw_fiov, 0);
	ftick->tk_aw_type = FT_A_FIOV;

	return 0;
}
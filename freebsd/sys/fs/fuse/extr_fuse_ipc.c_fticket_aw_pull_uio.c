#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uio {int dummy; } ;
struct fuse_ticket {int tk_aw_type; size_t tk_aw_bufsize; int /*<<< orphan*/  tk_aw_bufdata; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
#define  FT_A_BUF 129 
#define  FT_A_FIOV 128 
 int /*<<< orphan*/  fiov_adjust (TYPE_1__*,size_t) ; 
 TYPE_1__* fticket_resp (struct fuse_ticket*) ; 
 int /*<<< orphan*/  panic (char*,struct fuse_ticket*) ; 
 size_t uio_resid (struct uio*) ; 
 int uiomove (int /*<<< orphan*/ ,size_t,struct uio*) ; 

__attribute__((used)) static	inline
int
fticket_aw_pull_uio(struct fuse_ticket *ftick, struct uio *uio)
{
	int err = 0;
	size_t len = uio_resid(uio);

	if (len) {
		switch (ftick->tk_aw_type) {
		case FT_A_FIOV:
			fiov_adjust(fticket_resp(ftick), len);
			err = uiomove(fticket_resp(ftick)->base, len, uio);
			break;

		case FT_A_BUF:
			ftick->tk_aw_bufsize = len;
			err = uiomove(ftick->tk_aw_bufdata, len, uio);
			break;

		default:
			panic("FUSE: unknown answer type for ticket %p", ftick);
		}
	}
	return err;
}
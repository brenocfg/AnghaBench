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
struct knote {struct cuse_client* kn_hook; } ;
struct cuse_client {int cflags; } ;

/* Variables and functions */
 int CUSE_CLI_KNOTE_NEED_READ ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  cuse_mtx ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cuse_client_kqfilter_read_event(struct knote *kn, long hint)
{
	struct cuse_client *pcc;

	mtx_assert(&cuse_mtx, MA_OWNED);

	pcc = kn->kn_hook;
	return ((pcc->cflags & CUSE_CLI_KNOTE_NEED_READ) ? 1 : 0);
}
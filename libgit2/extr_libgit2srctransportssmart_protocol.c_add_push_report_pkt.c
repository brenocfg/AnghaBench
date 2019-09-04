#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * msg; void* ref; } ;
typedef  TYPE_1__ push_status ;
struct TYPE_14__ {int /*<<< orphan*/  unpack_ok; int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ git_push ;
struct TYPE_15__ {int /*<<< orphan*/  unpack_ok; } ;
typedef  TYPE_3__ git_pkt_unpack ;
struct TYPE_16__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_4__ git_pkt_ok ;
struct TYPE_17__ {int /*<<< orphan*/  msg; int /*<<< orphan*/  ref; } ;
typedef  TYPE_5__ git_pkt_ng ;
struct TYPE_18__ {int type; } ;
typedef  TYPE_6__ git_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 int GIT_ITEROVER ; 
#define  GIT_PKT_FLUSH 131 
#define  GIT_PKT_NG 130 
#define  GIT_PKT_OK 129 
#define  GIT_PKT_UNPACK 128 
 TYPE_1__* git__calloc (int,int) ; 
 void* git__strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_push_status_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_vector_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int add_push_report_pkt(git_push *push, git_pkt *pkt)
{
	push_status *status;

	switch (pkt->type) {
		case GIT_PKT_OK:
			status = git__calloc(1, sizeof(push_status));
			GIT_ERROR_CHECK_ALLOC(status);
			status->msg = NULL;
			status->ref = git__strdup(((git_pkt_ok *)pkt)->ref);
			if (!status->ref ||
				git_vector_insert(&push->status, status) < 0) {
				git_push_status_free(status);
				return -1;
			}
			break;
		case GIT_PKT_NG:
			status = git__calloc(1, sizeof(push_status));
			GIT_ERROR_CHECK_ALLOC(status);
			status->ref = git__strdup(((git_pkt_ng *)pkt)->ref);
			status->msg = git__strdup(((git_pkt_ng *)pkt)->msg);
			if (!status->ref || !status->msg ||
				git_vector_insert(&push->status, status) < 0) {
				git_push_status_free(status);
				return -1;
			}
			break;
		case GIT_PKT_UNPACK:
			push->unpack_ok = ((git_pkt_unpack *)pkt)->unpack_ok;
			break;
		case GIT_PKT_FLUSH:
			return GIT_ITEROVER;
		default:
			git_error_set(GIT_ERROR_NET, "report-status: protocol error");
			return -1;
	}

	return 0;
}
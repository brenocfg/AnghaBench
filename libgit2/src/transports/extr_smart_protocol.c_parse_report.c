#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  data; } ;
struct TYPE_16__ {int (* progress_cb ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  message_cb_payload; TYPE_2__ buffer; } ;
typedef  TYPE_1__ transport_smart ;
typedef  TYPE_2__ gitno_buffer ;
typedef  int /*<<< orphan*/  git_push ;
struct TYPE_18__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ git_pkt_progress ;
struct TYPE_19__ {int /*<<< orphan*/  error; } ;
typedef  TYPE_4__ git_pkt_err ;
typedef  int /*<<< orphan*/  git_pkt_data ;
struct TYPE_20__ {int type; } ;
typedef  TYPE_5__ git_pkt ;
struct TYPE_21__ {scalar_t__ size; } ;
typedef  TYPE_6__ git_buf ;

/* Variables and functions */
 TYPE_6__ GIT_BUF_INIT ; 
 int GIT_EBUFS ; 
 int GIT_EEOF ; 
 int GIT_ERROR ; 
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 int GIT_ITEROVER ; 
#define  GIT_PKT_DATA 130 
#define  GIT_PKT_ERR 129 
#define  GIT_PKT_PROGRESS 128 
 scalar_t__ INT_MAX ; 
 int add_push_report_pkt (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int add_push_report_sideband_pkt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_6__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  git_pkt_free (TYPE_5__*) ; 
 int git_pkt_parse_line (TYPE_5__**,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gitno_consume (TYPE_2__*,char const*) ; 
 int gitno_recv (TYPE_2__*) ; 
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_report(transport_smart *transport, git_push *push)
{
	git_pkt *pkt = NULL;
	const char *line_end = NULL;
	gitno_buffer *buf = &transport->buffer;
	int error, recvd;
	git_buf data_pkt_buf = GIT_BUF_INIT;

	for (;;) {
		if (buf->offset > 0)
			error = git_pkt_parse_line(&pkt, &line_end,
						   buf->data, buf->offset);
		else
			error = GIT_EBUFS;

		if (error < 0 && error != GIT_EBUFS) {
			error = -1;
			goto done;
		}

		if (error == GIT_EBUFS) {
			if ((recvd = gitno_recv(buf)) < 0) {
				error = recvd;
				goto done;
			}

			if (recvd == 0) {
				git_error_set(GIT_ERROR_NET, "early EOF");
				error = GIT_EEOF;
				goto done;
			}
			continue;
		}

		gitno_consume(buf, line_end);

		error = 0;

		switch (pkt->type) {
			case GIT_PKT_DATA:
				/* This is a sideband packet which contains other packets */
				error = add_push_report_sideband_pkt(push, (git_pkt_data *)pkt, &data_pkt_buf);
				break;
			case GIT_PKT_ERR:
				git_error_set(GIT_ERROR_NET, "report-status: Error reported: %s",
					((git_pkt_err *)pkt)->error);
				error = -1;
				break;
			case GIT_PKT_PROGRESS:
				if (transport->progress_cb) {
					git_pkt_progress *p = (git_pkt_progress *) pkt;

					if (p->len > INT_MAX) {
						git_error_set(GIT_ERROR_NET, "oversized progress message");
						error = GIT_ERROR;
						goto done;
					}

					error = transport->progress_cb(p->data, (int)p->len, transport->message_cb_payload);
				}
				break;
			default:
				error = add_push_report_pkt(push, pkt);
				break;
		}

		git_pkt_free(pkt);

		/* add_push_report_pkt returns GIT_ITEROVER when it receives a flush */
		if (error == GIT_ITEROVER) {
			error = 0;
			if (data_pkt_buf.size > 0) {
				/* If there was data remaining in the pack data buffer,
				 * then the server sent a partial pkt-line */
				git_error_set(GIT_ERROR_NET, "Incomplete pack data pkt-line");
				error = GIT_ERROR;
			}
			goto done;
		}

		if (error < 0) {
			goto done;
		}
	}
done:
	git_buf_dispose(&data_pkt_buf);
	return error;
}
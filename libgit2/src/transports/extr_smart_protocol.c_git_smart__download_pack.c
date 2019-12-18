#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_22__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {scalar_t__ val; } ;
struct TYPE_24__ {int /*<<< orphan*/  side_band_64k; int /*<<< orphan*/  side_band; } ;
struct TYPE_27__ {scalar_t__ offset; } ;
struct TYPE_26__ {int (* progress_cb ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;struct network_packetsize_payload* packetsize_payload; scalar_t__ (* packetsize_cb ) (scalar_t__,struct network_packetsize_payload*) ;int /*<<< orphan*/  message_cb_payload; TYPE_22__ cancelled; TYPE_1__ caps; TYPE_3__ buffer; } ;
typedef  TYPE_2__ transport_smart ;
struct network_packetsize_payload {int (* callback ) (TYPE_7__*,void*) ;scalar_t__ last_fired_bytes; void* payload; TYPE_7__* stats; int /*<<< orphan*/  member_0; } ;
struct git_odb_writepack {int (* append ) (struct git_odb_writepack*,int /*<<< orphan*/ ,scalar_t__,TYPE_7__*) ;int (* commit ) (struct git_odb_writepack*,TYPE_7__*) ;int /*<<< orphan*/  (* free ) (struct git_odb_writepack*) ;} ;
typedef  TYPE_3__ gitno_buffer ;
typedef  int /*<<< orphan*/  git_transport ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_28__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ git_pkt_progress ;
struct TYPE_29__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ git_pkt_data ;
struct TYPE_30__ {scalar_t__ type; } ;
typedef  TYPE_6__ git_pkt ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  int (* git_indexer_progress_cb ) (TYPE_7__*,void*) ;
struct TYPE_31__ {scalar_t__ received_bytes; } ;
typedef  TYPE_7__ git_indexer_progress ;

/* Variables and functions */
 int GIT_ERROR ; 
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 int GIT_EUSER ; 
 scalar_t__ GIT_PKT_DATA ; 
 scalar_t__ GIT_PKT_FLUSH ; 
 scalar_t__ GIT_PKT_PROGRESS ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  git__free (TYPE_6__*) ; 
 int /*<<< orphan*/  git_atomic_set (TYPE_22__*,int) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_odb_write_pack (struct git_odb_writepack**,int /*<<< orphan*/ *,int (*) (TYPE_7__*,void*),void*) ; 
 int /*<<< orphan*/  git_pkt_free (TYPE_6__*) ; 
 int git_repository_odb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ network_packetsize (scalar_t__,struct network_packetsize_payload*) ; 
 int no_sideband (TYPE_2__*,struct git_odb_writepack*,TYPE_3__*,TYPE_7__*) ; 
 int recv_pkt (TYPE_6__**,int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ stub1 (scalar_t__,struct network_packetsize_payload*) ; 
 int stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub3 (struct git_odb_writepack*,int /*<<< orphan*/ ,scalar_t__,TYPE_7__*) ; 
 int stub4 (TYPE_7__*,void*) ; 
 int stub5 (struct git_odb_writepack*,TYPE_7__*) ; 
 int /*<<< orphan*/  stub6 (struct git_odb_writepack*) ; 

int git_smart__download_pack(
	git_transport *transport,
	git_repository *repo,
	git_indexer_progress *stats,
	git_indexer_progress_cb progress_cb,
	void *progress_payload)
{
	transport_smart *t = (transport_smart *)transport;
	gitno_buffer *buf = &t->buffer;
	git_odb *odb;
	struct git_odb_writepack *writepack = NULL;
	int error = 0;
	struct network_packetsize_payload npp = {0};

	memset(stats, 0, sizeof(git_indexer_progress));

	if (progress_cb) {
		npp.callback = progress_cb;
		npp.payload = progress_payload;
		npp.stats = stats;
		t->packetsize_cb = &network_packetsize;
		t->packetsize_payload = &npp;

		/* We might have something in the buffer already from negotiate_fetch */
		if (t->buffer.offset > 0 && !t->cancelled.val)
			if (t->packetsize_cb(t->buffer.offset, t->packetsize_payload))
				git_atomic_set(&t->cancelled, 1);
	}

	if ((error = git_repository_odb__weakptr(&odb, repo)) < 0 ||
		((error = git_odb_write_pack(&writepack, odb, progress_cb, progress_payload)) != 0))
		goto done;

	/*
	 * If the remote doesn't support the side-band, we can feed
	 * the data directly to the pack writer. Otherwise, we need to
	 * check which one belongs there.
	 */
	if (!t->caps.side_band && !t->caps.side_band_64k) {
		error = no_sideband(t, writepack, buf, stats);
		goto done;
	}

	do {
		git_pkt *pkt = NULL;

		/* Check cancellation before network call */
		if (t->cancelled.val) {
			git_error_clear();
			error = GIT_EUSER;
			goto done;
		}

		if ((error = recv_pkt(&pkt, NULL, buf)) >= 0) {
			/* Check cancellation after network call */
			if (t->cancelled.val) {
				git_error_clear();
				error = GIT_EUSER;
			} else if (pkt->type == GIT_PKT_PROGRESS) {
				if (t->progress_cb) {
					git_pkt_progress *p = (git_pkt_progress *) pkt;

					if (p->len > INT_MAX) {
						git_error_set(GIT_ERROR_NET, "oversized progress message");
						error = GIT_ERROR;
						goto done;
					}

					error = t->progress_cb(p->data, (int)p->len, t->message_cb_payload);
				}
			} else if (pkt->type == GIT_PKT_DATA) {
				git_pkt_data *p = (git_pkt_data *) pkt;

				if (p->len)
					error = writepack->append(writepack, p->data, p->len, stats);
			} else if (pkt->type == GIT_PKT_FLUSH) {
				/* A flush indicates the end of the packfile */
				git__free(pkt);
				break;
			}
		}

		git_pkt_free(pkt);

		if (error < 0)
			goto done;

	} while (1);

	/*
	 * Trailing execution of progress_cb, if necessary...
	 * Only the callback through the npp datastructure currently
	 * updates the last_fired_bytes value. It is possible that
	 * progress has already been reported with the correct
	 * "received_bytes" value, but until (if?) this is unified
	 * then we will report progress again to be sure that the
	 * correct last received_bytes value is reported.
	 */
	if (npp.callback && npp.stats->received_bytes > npp.last_fired_bytes) {
		error = npp.callback(npp.stats, npp.payload);
		if (error != 0)
			goto done;
	}

	error = writepack->commit(writepack, stats);

done:
	if (writepack)
		writepack->free(writepack);
	if (progress_cb) {
		t->packetsize_cb = NULL;
		t->packetsize_payload = NULL;
	}

	return error;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ snd_una; scalar_t__ conv; int rmt_wnd; scalar_t__ current; scalar_t__ rcv_nxt; scalar_t__ rcv_wnd; int cwnd; scalar_t__ mss; int ssthresh; scalar_t__ incr; int /*<<< orphan*/  probe; scalar_t__ rx_rto; } ;
typedef  TYPE_1__ ikcpcb ;
struct TYPE_17__ {int /*<<< orphan*/  data; scalar_t__ len; scalar_t__ una; scalar_t__ sn; scalar_t__ ts; void* wnd; scalar_t__ frg; scalar_t__ cmd; scalar_t__ conv; } ;
typedef  scalar_t__ IUINT8 ;
typedef  scalar_t__ IUINT32 ;
typedef  void* IUINT16 ;
typedef  TYPE_2__ IKCPSEG ;

/* Variables and functions */
 int /*<<< orphan*/  IKCP_ASK_TELL ; 
 scalar_t__ IKCP_CMD_ACK ; 
 scalar_t__ IKCP_CMD_PUSH ; 
 scalar_t__ IKCP_CMD_WASK ; 
 scalar_t__ IKCP_CMD_WINS ; 
 int /*<<< orphan*/  IKCP_LOG_INPUT ; 
 int /*<<< orphan*/  IKCP_LOG_IN_ACK ; 
 int /*<<< orphan*/  IKCP_LOG_IN_DATA ; 
 int /*<<< orphan*/  IKCP_LOG_IN_PROBE ; 
 int /*<<< orphan*/  IKCP_LOG_IN_WINS ; 
 scalar_t__ IKCP_OVERHEAD ; 
 scalar_t__ _itimediff (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ikcp_ack_push (TYPE_1__*,scalar_t__,scalar_t__) ; 
 scalar_t__ ikcp_canlog (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* ikcp_decode16u (char const*,void**) ; 
 char* ikcp_decode32u (char const*,scalar_t__*) ; 
 char* ikcp_decode8u (char const*,scalar_t__*) ; 
 int /*<<< orphan*/  ikcp_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ikcp_parse_ack (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ikcp_parse_data (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ikcp_parse_fastack (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ikcp_parse_una (TYPE_1__*,scalar_t__) ; 
 TYPE_2__* ikcp_segment_new (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ikcp_shrink_buf (TYPE_1__*) ; 
 int /*<<< orphan*/  ikcp_update_ack (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

int ikcp_input(ikcpcb *kcp, const char *data, long size)
{
	IUINT32 prev_una = kcp->snd_una;
	IUINT32 maxack = 0, latest_ts = 0;
	int flag = 0;

	if (ikcp_canlog(kcp, IKCP_LOG_INPUT)) {
		ikcp_log(kcp, IKCP_LOG_INPUT, "[RI] %d bytes", (int)size);
	}

	if (data == NULL || (int)size < (int)IKCP_OVERHEAD) return -1;

	while (1) {
		IUINT32 ts, sn, len, una, conv;
		IUINT16 wnd;
		IUINT8 cmd, frg;
		IKCPSEG *seg;

		if (size < (int)IKCP_OVERHEAD) break;

		data = ikcp_decode32u(data, &conv);
		if (conv != kcp->conv) return -1;

		data = ikcp_decode8u(data, &cmd);
		data = ikcp_decode8u(data, &frg);
		data = ikcp_decode16u(data, &wnd);
		data = ikcp_decode32u(data, &ts);
		data = ikcp_decode32u(data, &sn);
		data = ikcp_decode32u(data, &una);
		data = ikcp_decode32u(data, &len);

		size -= IKCP_OVERHEAD;

		if ((long)size < (long)len || (int)len < 0) return -2;

		if (cmd != IKCP_CMD_PUSH && cmd != IKCP_CMD_ACK &&
			cmd != IKCP_CMD_WASK && cmd != IKCP_CMD_WINS) 
			return -3;

		kcp->rmt_wnd = wnd;
		ikcp_parse_una(kcp, una);
		ikcp_shrink_buf(kcp);

		if (cmd == IKCP_CMD_ACK) {
			if (_itimediff(kcp->current, ts) >= 0) {
				ikcp_update_ack(kcp, _itimediff(kcp->current, ts));
			}
			ikcp_parse_ack(kcp, sn);
			ikcp_shrink_buf(kcp);
			if (flag == 0) {
				flag = 1;
				maxack = sn;
				latest_ts = ts;
			}	else {
				if (_itimediff(sn, maxack) > 0) {
				#ifndef IKCP_FASTACK_CONSERVE
					maxack = sn;
					latest_ts = ts;
				#else
					if (_itimediff(ts, latest_ts) > 0) {
						maxack = sn;
						latest_ts = ts;
					}
				#endif
				}
			}
			if (ikcp_canlog(kcp, IKCP_LOG_IN_ACK)) {
				ikcp_log(kcp, IKCP_LOG_IN_DATA, 
					"input ack: sn=%lu rtt=%ld rto=%ld", (unsigned long)sn, 
					(long)_itimediff(kcp->current, ts),
					(long)kcp->rx_rto);
			}
		}
		else if (cmd == IKCP_CMD_PUSH) {
			if (ikcp_canlog(kcp, IKCP_LOG_IN_DATA)) {
				ikcp_log(kcp, IKCP_LOG_IN_DATA, 
					"input psh: sn=%lu ts=%lu", (unsigned long)sn, (unsigned long)ts);
			}
			if (_itimediff(sn, kcp->rcv_nxt + kcp->rcv_wnd) < 0) {
				ikcp_ack_push(kcp, sn, ts);
				if (_itimediff(sn, kcp->rcv_nxt) >= 0) {
					seg = ikcp_segment_new(kcp, len);
					seg->conv = conv;
					seg->cmd = cmd;
					seg->frg = frg;
					seg->wnd = wnd;
					seg->ts = ts;
					seg->sn = sn;
					seg->una = una;
					seg->len = len;

					if (len > 0) {
						memcpy(seg->data, data, len);
					}

					ikcp_parse_data(kcp, seg);
				}
			}
		}
		else if (cmd == IKCP_CMD_WASK) {
			// ready to send back IKCP_CMD_WINS in ikcp_flush
			// tell remote my window size
			kcp->probe |= IKCP_ASK_TELL;
			if (ikcp_canlog(kcp, IKCP_LOG_IN_PROBE)) {
				ikcp_log(kcp, IKCP_LOG_IN_PROBE, "input probe");
			}
		}
		else if (cmd == IKCP_CMD_WINS) {
			// do nothing
			if (ikcp_canlog(kcp, IKCP_LOG_IN_WINS)) {
				ikcp_log(kcp, IKCP_LOG_IN_WINS,
					"input wins: %lu", (unsigned long)(wnd));
			}
		}
		else {
			return -3;
		}

		data += len;
		size -= len;
	}

	if (flag != 0) {
		ikcp_parse_fastack(kcp, maxack, latest_ts);
	}

	if (_itimediff(kcp->snd_una, prev_una) > 0) {
		if (kcp->cwnd < kcp->rmt_wnd) {
			IUINT32 mss = kcp->mss;
			if (kcp->cwnd < kcp->ssthresh) {
				kcp->cwnd++;
				kcp->incr += mss;
			}	else {
				if (kcp->incr < mss) kcp->incr = mss;
				kcp->incr += (mss * mss) / kcp->incr + (mss / 16);
				if ((kcp->cwnd + 1) * mss <= kcp->incr) {
					kcp->cwnd++;
				}
			}
			if (kcp->cwnd > kcp->rmt_wnd) {
				kcp->cwnd = kcp->rmt_wnd;
				kcp->incr = kcp->rmt_wnd * mss;
			}
		}
	}

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int port_caps32; } ;
struct adapter {TYPE_1__ params; int /*<<< orphan*/  pf; int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 scalar_t__ A_TP_KEEP_IDLE ; 
 scalar_t__ A_TP_KEEP_INTVL ; 
 scalar_t__ A_TP_RSS_CONFIG_TNL ; 
 scalar_t__ A_TP_RXT_MAX ; 
 scalar_t__ A_TP_RXT_MIN ; 
 scalar_t__ A_TP_SHIFT_CNT ; 
 scalar_t__ A_TP_TCP_BACKOFF_REG0 ; 
 int /*<<< orphan*/  CPLFW4MSG_ENCAP ; 
 int FW_PARAM_PFVF (int /*<<< orphan*/ ) ; 
 int G_MASKSIZE (int /*<<< orphan*/ ) ; 
 int M_KEEPALIVEIDLE ; 
 int M_KEEPALIVEINTVL ; 
 int M_KEEPALIVEMAXR1 ; 
 int M_KEEPALIVEMAXR2 ; 
 int M_MASKFILTER ; 
 int M_RXTMAX ; 
 int M_RXTMIN ; 
 int M_RXTSHIFTMAXR1 ; 
 int M_RXTSHIFTMAXR2 ; 
 int M_TIMERBACKOFFINDEX0 ; 
 int /*<<< orphan*/  PORT_CAPS32 ; 
 int V_KEEPALIVEIDLE (int) ; 
 int V_KEEPALIVEINTVL (int) ; 
 int V_KEEPALIVEMAXR1 (int) ; 
 int V_KEEPALIVEMAXR2 (int) ; 
 int V_MASKFILTER (int) ; 
 int V_RXTMAX (int) ; 
 int V_RXTMIN (int) ; 
 int V_RXTSHIFTMAXR1 (int) ; 
 int V_RXTSHIFTMAXR2 (int) ; 
 int nitems (int*) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,scalar_t__) ; 
 scalar_t__ t4_set_params (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  t4_set_reg_field (struct adapter*,scalar_t__,int,int) ; 
 int t4_toe_keepalive_count ; 
 scalar_t__ t4_toe_keepalive_idle ; 
 scalar_t__ t4_toe_keepalive_interval ; 
 int* t4_toe_rexmt_backoff ; 
 int t4_toe_rexmt_count ; 
 scalar_t__ t4_toe_rexmt_max ; 
 scalar_t__ t4_toe_rexmt_min ; 
 int us_to_tcp_ticks (struct adapter*,scalar_t__) ; 

__attribute__((used)) static int
set_params__post_init(struct adapter *sc)
{
	uint32_t param, val;
#ifdef TCP_OFFLOAD
	int i, v, shift;
#endif

	/* ask for encapsulated CPLs */
	param = FW_PARAM_PFVF(CPLFW4MSG_ENCAP);
	val = 1;
	(void)t4_set_params(sc, sc->mbox, sc->pf, 0, 1, &param, &val);

	/* Enable 32b port caps if the firmware supports it. */
	param = FW_PARAM_PFVF(PORT_CAPS32);
	val = 1;
	if (t4_set_params(sc, sc->mbox, sc->pf, 0, 1, &param, &val) == 0)
		sc->params.port_caps32 = 1;

	/* Let filter + maskhash steer to a part of the VI's RSS region. */
	val = 1 << (G_MASKSIZE(t4_read_reg(sc, A_TP_RSS_CONFIG_TNL)) - 1);
	t4_set_reg_field(sc, A_TP_RSS_CONFIG_TNL, V_MASKFILTER(M_MASKFILTER),
	    V_MASKFILTER(val - 1));

#ifdef TCP_OFFLOAD
	/*
	 * Override the TOE timers with user provided tunables.  This is not the
	 * recommended way to change the timers (the firmware config file is) so
	 * these tunables are not documented.
	 *
	 * All the timer tunables are in microseconds.
	 */
	if (t4_toe_keepalive_idle != 0) {
		v = us_to_tcp_ticks(sc, t4_toe_keepalive_idle);
		v &= M_KEEPALIVEIDLE;
		t4_set_reg_field(sc, A_TP_KEEP_IDLE,
		    V_KEEPALIVEIDLE(M_KEEPALIVEIDLE), V_KEEPALIVEIDLE(v));
	}
	if (t4_toe_keepalive_interval != 0) {
		v = us_to_tcp_ticks(sc, t4_toe_keepalive_interval);
		v &= M_KEEPALIVEINTVL;
		t4_set_reg_field(sc, A_TP_KEEP_INTVL,
		    V_KEEPALIVEINTVL(M_KEEPALIVEINTVL), V_KEEPALIVEINTVL(v));
	}
	if (t4_toe_keepalive_count != 0) {
		v = t4_toe_keepalive_count & M_KEEPALIVEMAXR2;
		t4_set_reg_field(sc, A_TP_SHIFT_CNT,
		    V_KEEPALIVEMAXR1(M_KEEPALIVEMAXR1) |
		    V_KEEPALIVEMAXR2(M_KEEPALIVEMAXR2),
		    V_KEEPALIVEMAXR1(1) | V_KEEPALIVEMAXR2(v));
	}
	if (t4_toe_rexmt_min != 0) {
		v = us_to_tcp_ticks(sc, t4_toe_rexmt_min);
		v &= M_RXTMIN;
		t4_set_reg_field(sc, A_TP_RXT_MIN,
		    V_RXTMIN(M_RXTMIN), V_RXTMIN(v));
	}
	if (t4_toe_rexmt_max != 0) {
		v = us_to_tcp_ticks(sc, t4_toe_rexmt_max);
		v &= M_RXTMAX;
		t4_set_reg_field(sc, A_TP_RXT_MAX,
		    V_RXTMAX(M_RXTMAX), V_RXTMAX(v));
	}
	if (t4_toe_rexmt_count != 0) {
		v = t4_toe_rexmt_count & M_RXTSHIFTMAXR2;
		t4_set_reg_field(sc, A_TP_SHIFT_CNT,
		    V_RXTSHIFTMAXR1(M_RXTSHIFTMAXR1) |
		    V_RXTSHIFTMAXR2(M_RXTSHIFTMAXR2),
		    V_RXTSHIFTMAXR1(1) | V_RXTSHIFTMAXR2(v));
	}
	for (i = 0; i < nitems(t4_toe_rexmt_backoff); i++) {
		if (t4_toe_rexmt_backoff[i] != -1) {
			v = t4_toe_rexmt_backoff[i] & M_TIMERBACKOFFINDEX0;
			shift = (i & 3) << 3;
			t4_set_reg_field(sc, A_TP_TCP_BACKOFF_REG0 + (i & ~3),
			    M_TIMERBACKOFFINDEX0 << shift, v << shift);
		}
	}
#endif
	return (0);
}
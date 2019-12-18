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
typedef  int /*<<< orphan*/  uint64_t ;
struct tgec_regs {int dummy; } ;
typedef  enum tgec_counters { ____Placeholder_tgec_counters } tgec_counters ;

/* Variables and functions */
#define  E_TGEC_COUNTER_R1023 153 
#define  E_TGEC_COUNTER_R127 152 
#define  E_TGEC_COUNTER_R1518 151 
#define  E_TGEC_COUNTER_R1519X 150 
#define  E_TGEC_COUNTER_R255 149 
#define  E_TGEC_COUNTER_R511 148 
#define  E_TGEC_COUNTER_R64 147 
#define  E_TGEC_COUNTER_RALN 146 
#define  E_TGEC_COUNTER_RBCA 145 
#define  E_TGEC_COUNTER_RDRP 144 
#define  E_TGEC_COUNTER_RERR 143 
#define  E_TGEC_COUNTER_RMCA 142 
#define  E_TGEC_COUNTER_ROCT 141 
#define  E_TGEC_COUNTER_RPKT 140 
#define  E_TGEC_COUNTER_RUCA 139 
#define  E_TGEC_COUNTER_RXPF 138 
#define  E_TGEC_COUNTER_TBCA 137 
#define  E_TGEC_COUNTER_TERR 136 
#define  E_TGEC_COUNTER_TMCA 135 
#define  E_TGEC_COUNTER_TOCT 134 
#define  E_TGEC_COUNTER_TRFRG 133 
#define  E_TGEC_COUNTER_TRJBR 132 
#define  E_TGEC_COUNTER_TROVR 131 
#define  E_TGEC_COUNTER_TRUND 130 
#define  E_TGEC_COUNTER_TUCA 129 
#define  E_TGEC_COUNTER_TXPF 128 
 int /*<<< orphan*/  GET_TGEC_CNTR_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r1023 ; 
 int /*<<< orphan*/  r127 ; 
 int /*<<< orphan*/  r1518 ; 
 int /*<<< orphan*/  r1519x ; 
 int /*<<< orphan*/  r255 ; 
 int /*<<< orphan*/  r511 ; 
 int /*<<< orphan*/  r64 ; 
 int /*<<< orphan*/  raln ; 
 int /*<<< orphan*/  rbca ; 
 int /*<<< orphan*/  rdrp ; 
 int /*<<< orphan*/  rerr ; 
 int /*<<< orphan*/  rmca ; 
 int /*<<< orphan*/  roct ; 
 int /*<<< orphan*/  rpkt ; 
 int /*<<< orphan*/  ruca ; 
 int /*<<< orphan*/  rxpf ; 
 int /*<<< orphan*/  tbca ; 
 int /*<<< orphan*/  terr ; 
 int /*<<< orphan*/  tmca ; 
 int /*<<< orphan*/  toct ; 
 int /*<<< orphan*/  trfrg ; 
 int /*<<< orphan*/  trjbr ; 
 int /*<<< orphan*/  trovr ; 
 int /*<<< orphan*/  trund ; 
 int /*<<< orphan*/  tuca ; 
 int /*<<< orphan*/  txpf ; 

uint64_t fman_tgec_get_counter(struct tgec_regs *regs, enum tgec_counters reg_name)
{
	uint64_t ret_val;

	switch (reg_name) {
	case E_TGEC_COUNTER_R64:
		ret_val = GET_TGEC_CNTR_64(r64);
		break;
	case E_TGEC_COUNTER_R127:
		ret_val = GET_TGEC_CNTR_64(r127);
		break;
	case E_TGEC_COUNTER_R255:
		ret_val = GET_TGEC_CNTR_64(r255);
		break;
	case E_TGEC_COUNTER_R511:
		ret_val = GET_TGEC_CNTR_64(r511);
		break;
	case E_TGEC_COUNTER_R1023:
		ret_val = GET_TGEC_CNTR_64(r1023);
		break;
	case E_TGEC_COUNTER_R1518:
		ret_val = GET_TGEC_CNTR_64(r1518);
		break;
	case E_TGEC_COUNTER_R1519X:
		ret_val = GET_TGEC_CNTR_64(r1519x);
		break;
	case E_TGEC_COUNTER_TRFRG:
		ret_val = GET_TGEC_CNTR_64(trfrg);
		break;
	case E_TGEC_COUNTER_TRJBR:
		ret_val = GET_TGEC_CNTR_64(trjbr);
		break;
	case E_TGEC_COUNTER_RDRP:
		ret_val = GET_TGEC_CNTR_64(rdrp);
		break;
	case E_TGEC_COUNTER_RALN:
		ret_val = GET_TGEC_CNTR_64(raln);
		break;
	case E_TGEC_COUNTER_TRUND:
		ret_val = GET_TGEC_CNTR_64(trund);
		break;
	case E_TGEC_COUNTER_TROVR:
		ret_val = GET_TGEC_CNTR_64(trovr);
		break;
	case E_TGEC_COUNTER_RXPF:
		ret_val = GET_TGEC_CNTR_64(rxpf);
		break;
	case E_TGEC_COUNTER_TXPF:
		ret_val = GET_TGEC_CNTR_64(txpf);
		break;
	case E_TGEC_COUNTER_ROCT:
		ret_val = GET_TGEC_CNTR_64(roct);
		break;
	case E_TGEC_COUNTER_RMCA:
		ret_val = GET_TGEC_CNTR_64(rmca);
		break;
	case E_TGEC_COUNTER_RBCA:
		ret_val = GET_TGEC_CNTR_64(rbca);
		break;
	case E_TGEC_COUNTER_RPKT:
		ret_val = GET_TGEC_CNTR_64(rpkt);
		break;
	case E_TGEC_COUNTER_RUCA:
		ret_val = GET_TGEC_CNTR_64(ruca);
		break;
	case E_TGEC_COUNTER_RERR:
		ret_val = GET_TGEC_CNTR_64(rerr);
		break;
	case E_TGEC_COUNTER_TOCT:
		ret_val = GET_TGEC_CNTR_64(toct);
		break;
	case E_TGEC_COUNTER_TMCA:
		ret_val = GET_TGEC_CNTR_64(tmca);
		break;
	case E_TGEC_COUNTER_TBCA:
		ret_val = GET_TGEC_CNTR_64(tbca);
		break;
	case E_TGEC_COUNTER_TUCA:
		ret_val = GET_TGEC_CNTR_64(tuca);
		break;
	case E_TGEC_COUNTER_TERR:
		ret_val = GET_TGEC_CNTR_64(terr);
		break;
	default:
		ret_val = 0;
	}

	return ret_val;
}
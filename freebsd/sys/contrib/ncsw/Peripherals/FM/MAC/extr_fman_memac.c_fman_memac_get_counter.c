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
struct memac_regs {int dummy; } ;
typedef  enum memac_counters { ____Placeholder_memac_counters } memac_counters ;

/* Variables and functions */
#define  E_MEMAC_COUNTER_R1023 153 
#define  E_MEMAC_COUNTER_R127 152 
#define  E_MEMAC_COUNTER_R1518 151 
#define  E_MEMAC_COUNTER_R1519X 150 
#define  E_MEMAC_COUNTER_R255 149 
#define  E_MEMAC_COUNTER_R511 148 
#define  E_MEMAC_COUNTER_R64 147 
#define  E_MEMAC_COUNTER_RALN 146 
#define  E_MEMAC_COUNTER_RBCA 145 
#define  E_MEMAC_COUNTER_RDRP 144 
#define  E_MEMAC_COUNTER_RERR 143 
#define  E_MEMAC_COUNTER_RFRG 142 
#define  E_MEMAC_COUNTER_RJBR 141 
#define  E_MEMAC_COUNTER_RMCA 140 
#define  E_MEMAC_COUNTER_ROCT 139 
#define  E_MEMAC_COUNTER_ROVR 138 
#define  E_MEMAC_COUNTER_RPKT 137 
#define  E_MEMAC_COUNTER_RUCA 136 
#define  E_MEMAC_COUNTER_RXPF 135 
#define  E_MEMAC_COUNTER_TBCA 134 
#define  E_MEMAC_COUNTER_TERR 133 
#define  E_MEMAC_COUNTER_TMCA 132 
#define  E_MEMAC_COUNTER_TOCT 131 
#define  E_MEMAC_COUNTER_TUCA 130 
#define  E_MEMAC_COUNTER_TUND 129 
#define  E_MEMAC_COUNTER_TXPF 128 
 int /*<<< orphan*/  GET_MEMAC_CNTR_64 (int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  rfrg ; 
 int /*<<< orphan*/  rjbr ; 
 int /*<<< orphan*/  rmca ; 
 int /*<<< orphan*/  roct ; 
 int /*<<< orphan*/  rovr ; 
 int /*<<< orphan*/  rpkt ; 
 int /*<<< orphan*/  ruca ; 
 int /*<<< orphan*/  rxpf ; 
 int /*<<< orphan*/  tbca ; 
 int /*<<< orphan*/  terr ; 
 int /*<<< orphan*/  tmca ; 
 int /*<<< orphan*/  toct ; 
 int /*<<< orphan*/  tuca ; 
 int /*<<< orphan*/  tund ; 
 int /*<<< orphan*/  txpf ; 

uint64_t fman_memac_get_counter(struct memac_regs *regs,
                enum memac_counters reg_name)
{
    uint64_t ret_val;

    switch (reg_name) {
    case E_MEMAC_COUNTER_R64:
        ret_val = GET_MEMAC_CNTR_64(r64);
        break;
    case E_MEMAC_COUNTER_R127:
        ret_val = GET_MEMAC_CNTR_64(r127);
        break;
    case E_MEMAC_COUNTER_R255:
        ret_val = GET_MEMAC_CNTR_64(r255);
        break;
    case E_MEMAC_COUNTER_R511:
        ret_val = GET_MEMAC_CNTR_64(r511);
        break;
    case E_MEMAC_COUNTER_R1023:
        ret_val = GET_MEMAC_CNTR_64(r1023);
        break;
    case E_MEMAC_COUNTER_R1518:
        ret_val = GET_MEMAC_CNTR_64(r1518);
        break;
    case E_MEMAC_COUNTER_R1519X:
        ret_val = GET_MEMAC_CNTR_64(r1519x);
        break;
    case E_MEMAC_COUNTER_RFRG:
        ret_val = GET_MEMAC_CNTR_64(rfrg);
        break;
    case E_MEMAC_COUNTER_RJBR:
        ret_val = GET_MEMAC_CNTR_64(rjbr);
        break;
    case E_MEMAC_COUNTER_RDRP:
        ret_val = GET_MEMAC_CNTR_64(rdrp);
        break;
    case E_MEMAC_COUNTER_RALN:
        ret_val = GET_MEMAC_CNTR_64(raln);
        break;
    case E_MEMAC_COUNTER_TUND:
        ret_val = GET_MEMAC_CNTR_64(tund);
        break;
    case E_MEMAC_COUNTER_ROVR:
        ret_val = GET_MEMAC_CNTR_64(rovr);
        break;
    case E_MEMAC_COUNTER_RXPF:
        ret_val = GET_MEMAC_CNTR_64(rxpf);
        break;
    case E_MEMAC_COUNTER_TXPF:
        ret_val = GET_MEMAC_CNTR_64(txpf);
        break;
    case E_MEMAC_COUNTER_ROCT:
        ret_val = GET_MEMAC_CNTR_64(roct);
        break;
    case E_MEMAC_COUNTER_RMCA:
        ret_val = GET_MEMAC_CNTR_64(rmca);
        break;
    case E_MEMAC_COUNTER_RBCA:
        ret_val = GET_MEMAC_CNTR_64(rbca);
        break;
    case E_MEMAC_COUNTER_RPKT:
        ret_val = GET_MEMAC_CNTR_64(rpkt);
        break;
    case E_MEMAC_COUNTER_RUCA:
        ret_val = GET_MEMAC_CNTR_64(ruca);
        break;
    case E_MEMAC_COUNTER_RERR:
        ret_val = GET_MEMAC_CNTR_64(rerr);
        break;
    case E_MEMAC_COUNTER_TOCT:
        ret_val = GET_MEMAC_CNTR_64(toct);
        break;
    case E_MEMAC_COUNTER_TMCA:
        ret_val = GET_MEMAC_CNTR_64(tmca);
        break;
    case E_MEMAC_COUNTER_TBCA:
        ret_val = GET_MEMAC_CNTR_64(tbca);
        break;
    case E_MEMAC_COUNTER_TUCA:
        ret_val = GET_MEMAC_CNTR_64(tuca);
        break;
    case E_MEMAC_COUNTER_TERR:
        ret_val = GET_MEMAC_CNTR_64(terr);
        break;
    default:
        ret_val = 0;
    }

    return ret_val;
}
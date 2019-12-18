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
typedef  size_t varInds_t ;
typedef  size_t const U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*) ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int,int) ; 
#define  NUM_PARAMS 136 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
#define  clog_ind 135 
#define  fadt_ind 134 
#define  hlog_ind 133 
 size_t const* mintable ; 
#define  mml_ind 132 
 scalar_t__* rangetable ; 
#define  slog_ind 131 
#define  strt_ind 130 
#define  tlen_ind 129 
 size_t const* tlen_table ; 
#define  wlog_ind 128 

__attribute__((used)) static U32 rangeMap(varInds_t param, int ind)
{
    U32 const uind = (U32)MAX(MIN(ind, (int)rangetable[param] - 1), 0);
    switch(param) {
        case wlog_ind: /* using default: triggers -Wswitch-enum */
        case clog_ind:
        case hlog_ind:
        case slog_ind:
        case mml_ind:
        case strt_ind:
            return mintable[param] + uind;
        case tlen_ind:
            return tlen_table[uind];
        case fadt_ind: /* 0, 1, 2 -> -1, 0, 1 */
            return uind - 1;
        case NUM_PARAMS:
        default:;
    }
    DISPLAY("Error, not a valid param\n ");
    assert(0);
    return (U32)-1;
}
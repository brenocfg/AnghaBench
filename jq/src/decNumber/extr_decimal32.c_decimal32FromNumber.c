#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uInt ;
struct TYPE_15__ {int /*<<< orphan*/  bytes; } ;
typedef  TYPE_1__ decimal32 ;
struct TYPE_16__ {scalar_t__ exponent; int digits; int bits; scalar_t__* lsu; } ;
typedef  TYPE_2__ decNumber ;
struct TYPE_17__ {int status; int /*<<< orphan*/  round; } ;
typedef  TYPE_3__ decContext ;
typedef  scalar_t__ Int ;

/* Variables and functions */
 int* BIN2DPD ; 
 int DECDPUN ; 
 scalar_t__ DECIMAL32_Bias ; 
 int DECIMAL32_Ehigh ; 
 scalar_t__ DECIMAL32_Emax ; 
 scalar_t__ DECIMAL32_Emin ; 
 int DECIMAL32_Pmax ; 
 int DECIMAL_Inf ; 
 int DECIMAL_NaN ; 
 int DECIMAL_sNaN ; 
 int DECINF ; 
 int DECNAN ; 
 int DECNEG ; 
 int DECSPECIAL ; 
 int DEC_Clamped ; 
 int /*<<< orphan*/  DEC_INIT_DECIMAL32 ; 
 int /*<<< orphan*/  UBFROMUI (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  decContextDefault (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decContextSetStatus (TYPE_3__*,int) ; 
 int /*<<< orphan*/  decDigitsToDPD (TYPE_2__ const*,int*,scalar_t__) ; 
 scalar_t__ decNumberIsZero (TYPE_2__ const*) ; 
 int /*<<< orphan*/  decNumberPlus (TYPE_2__*,TYPE_2__ const*,TYPE_3__*) ; 

decimal32 * decimal32FromNumber(decimal32 *d32, const decNumber *dn,
                              decContext *set) {
  uInt status=0;                   // status accumulator
  Int ae;                          // adjusted exponent
  decNumber  dw;                   // work
  decContext dc;                   // ..
  uInt comb, exp;                  // ..
  uInt uiwork;                     // for macros
  uInt targ=0;                     // target 32-bit

  // If the number has too many digits, or the exponent could be
  // out of range then reduce the number under the appropriate
  // constraints.  This could push the number to Infinity or zero,
  // so this check and rounding must be done before generating the
  // decimal32]
  ae=dn->exponent+dn->digits-1;              // [0 if special]
  if (dn->digits>DECIMAL32_Pmax              // too many digits
   || ae>DECIMAL32_Emax                      // likely overflow
   || ae<DECIMAL32_Emin) {                   // likely underflow
    decContextDefault(&dc, DEC_INIT_DECIMAL32); // [no traps]
    dc.round=set->round;                     // use supplied rounding
    decNumberPlus(&dw, dn, &dc);             // (round and check)
    // [this changes -0 to 0, so enforce the sign...]
    dw.bits|=dn->bits&DECNEG;
    status=dc.status;                        // save status
    dn=&dw;                                  // use the work number
    } // maybe out of range

  if (dn->bits&DECSPECIAL) {                      // a special value
    if (dn->bits&DECINF) targ=DECIMAL_Inf<<24;
     else {                                       // sNaN or qNaN
      if ((*dn->lsu!=0 || dn->digits>1)           // non-zero coefficient
       && (dn->digits<DECIMAL32_Pmax)) {          // coefficient fits
        decDigitsToDPD(dn, &targ, 0);
        }
      if (dn->bits&DECNAN) targ|=DECIMAL_NaN<<24;
       else targ|=DECIMAL_sNaN<<24;
      } // a NaN
    } // special

   else { // is finite
    if (decNumberIsZero(dn)) {               // is a zero
      // set and clamp exponent
      if (dn->exponent<-DECIMAL32_Bias) {
        exp=0;                               // low clamp
        status|=DEC_Clamped;
        }
       else {
        exp=dn->exponent+DECIMAL32_Bias;     // bias exponent
        if (exp>DECIMAL32_Ehigh) {           // top clamp
          exp=DECIMAL32_Ehigh;
          status|=DEC_Clamped;
          }
        }
      comb=(exp>>3) & 0x18;             // msd=0, exp top 2 bits ..
      }
     else {                             // non-zero finite number
      uInt msd;                         // work
      Int pad=0;                        // coefficient pad digits

      // the dn is known to fit, but it may need to be padded
      exp=(uInt)(dn->exponent+DECIMAL32_Bias);    // bias exponent
      if (exp>DECIMAL32_Ehigh) {                  // fold-down case
        pad=exp-DECIMAL32_Ehigh;
        exp=DECIMAL32_Ehigh;                      // [to maximum]
        status|=DEC_Clamped;
        }

      // fastpath common case
      if (DECDPUN==3 && pad==0) {
        targ=BIN2DPD[dn->lsu[0]];
        if (dn->digits>3) targ|=(uInt)(BIN2DPD[dn->lsu[1]])<<10;
        msd=(dn->digits==7 ? dn->lsu[2] : 0);
        }
       else { // general case
        decDigitsToDPD(dn, &targ, pad);
        // save and clear the top digit
        msd=targ>>20;
        targ&=0x000fffff;
        }

      // create the combination field
      if (msd>=8) comb=0x18 | ((exp>>5) & 0x06) | (msd & 0x01);
             else comb=((exp>>3) & 0x18) | msd;
      }
    targ|=comb<<26;                // add combination field ..
    targ|=(exp&0x3f)<<20;          // .. and exponent continuation
    } // finite

  if (dn->bits&DECNEG) targ|=0x80000000;  // add sign bit

  // now write to storage; this is endian
  UBFROMUI(d32->bytes, targ);      // directly store the int

  if (status!=0) decContextSetStatus(set, status); // pass on status
  // decimal32Show(d32);
  return d32;
  }
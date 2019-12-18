#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uInt ;
struct TYPE_8__ {int /*<<< orphan*/  bytes; } ;
typedef  TYPE_1__ decimal32 ;
struct TYPE_9__ {scalar_t__ exponent; int /*<<< orphan*/  bits; } ;
typedef  TYPE_2__ decNumber ;

/* Variables and functions */
 int* COMBEXP ; 
 int* COMBMSD ; 
 scalar_t__ DECIMAL32_Bias ; 
 int /*<<< orphan*/  DECINF ; 
 int /*<<< orphan*/  DECNAN ; 
 int /*<<< orphan*/  DECNEG ; 
 int /*<<< orphan*/  DECSNAN ; 
 int UBTOUI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decDigitsFromDPD (TYPE_2__*,int*,int) ; 
 int /*<<< orphan*/  decNumberZero (TYPE_2__*) ; 

decNumber * decimal32ToNumber(const decimal32 *d32, decNumber *dn) {
  uInt msd;                        // coefficient MSD
  uInt exp;                        // exponent top two bits
  uInt comb;                       // combination field
  uInt sour;                       // source 32-bit
  uInt uiwork;                     // for macros

  // load source from storage; this is endian
  sour=UBTOUI(d32->bytes);         // directly load the int

  comb=(sour>>26)&0x1f;            // combination field

  decNumberZero(dn);               // clean number
  if (sour&0x80000000) dn->bits=DECNEG; // set sign if negative

  msd=COMBMSD[comb];               // decode the combination field
  exp=COMBEXP[comb];               // ..

  if (exp==3) {                    // is a special
    if (msd==0) {
      dn->bits|=DECINF;
      return dn;                   // no coefficient needed
      }
    else if (sour&0x02000000) dn->bits|=DECSNAN;
    else dn->bits|=DECNAN;
    msd=0;                         // no top digit
    }
   else {                          // is a finite number
    dn->exponent=(exp<<6)+((sour>>20)&0x3f)-DECIMAL32_Bias; // unbiased
    }

  // get the coefficient
  sour&=0x000fffff;                // clean coefficient continuation
  if (msd) {                       // non-zero msd
    sour|=msd<<20;                 // prefix to coefficient
    decDigitsFromDPD(dn, &sour, 3); // process 3 declets
    return dn;
    }
  // msd=0
  if (!sour) return dn;            // easy: coefficient is 0
  if (sour&0x000ffc00)             // need 2 declets?
    decDigitsFromDPD(dn, &sour, 2); // process 2 declets
   else
    decDigitsFromDPD(dn, &sour, 1); // process 1 declet
  return dn;
  }
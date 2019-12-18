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
typedef  size_t uInt ;
struct TYPE_8__ {scalar_t__ bytes; } ;
typedef  TYPE_1__ decimal64 ;
struct TYPE_9__ {scalar_t__ exponent; int /*<<< orphan*/  bits; } ;
typedef  TYPE_2__ decNumber ;
typedef  int Int ;

/* Variables and functions */
 size_t* COMBEXP ; 
 size_t* COMBMSD ; 
 scalar_t__ DECIMAL64_Bias ; 
 int /*<<< orphan*/  DECINF ; 
 scalar_t__ DECLITEND ; 
 int /*<<< orphan*/  DECNAN ; 
 int /*<<< orphan*/  DECNEG ; 
 int /*<<< orphan*/  DECSNAN ; 
 int UBTOUI (scalar_t__) ; 
 int /*<<< orphan*/  decDigitsFromDPD (TYPE_2__*,size_t*,int) ; 
 int /*<<< orphan*/  decNumberZero (TYPE_2__*) ; 
 int sourhi ; 
 int sourlo ; 

decNumber * decimal64ToNumber(const decimal64 *d64, decNumber *dn) {
  uInt msd;                        // coefficient MSD
  uInt exp;                        // exponent top two bits
  uInt comb;                       // combination field
  Int  need;                       // work
  uInt uiwork;                     // for macros
  uInt sourar[2];                  // source 64-bit
  #define sourhi sourar[1]         // name the word with the sign
  #define sourlo sourar[0]         // and the lower word

  // load source from storage; this is endian
  if (DECLITEND) {
    sourlo=UBTOUI(d64->bytes  );   // directly load the low int
    sourhi=UBTOUI(d64->bytes+4);   // then the high int
    }
   else {
    sourhi=UBTOUI(d64->bytes  );   // directly load the high int
    sourlo=UBTOUI(d64->bytes+4);   // then the low int
    }

  comb=(sourhi>>26)&0x1f;          // combination field

  decNumberZero(dn);               // clean number
  if (sourhi&0x80000000) dn->bits=DECNEG; // set sign if negative

  msd=COMBMSD[comb];               // decode the combination field
  exp=COMBEXP[comb];               // ..

  if (exp==3) {                    // is a special
    if (msd==0) {
      dn->bits|=DECINF;
      return dn;                   // no coefficient needed
      }
    else if (sourhi&0x02000000) dn->bits|=DECSNAN;
    else dn->bits|=DECNAN;
    msd=0;                         // no top digit
    }
   else {                          // is a finite number
    dn->exponent=(exp<<8)+((sourhi>>18)&0xff)-DECIMAL64_Bias; // unbiased
    }

  // get the coefficient
  sourhi&=0x0003ffff;              // clean coefficient continuation
  if (msd) {                       // non-zero msd
    sourhi|=msd<<18;               // prefix to coefficient
    need=6;                        // process 6 declets
    }
   else { // msd=0
    if (!sourhi) {                 // top word 0
      if (!sourlo) return dn;      // easy: coefficient is 0
      need=3;                      // process at least 3 declets
      if (sourlo&0xc0000000) need++; // process 4 declets
      // [could reduce some more, here]
      }
     else {                        // some bits in top word, msd=0
      need=4;                      // process at least 4 declets
      if (sourhi&0x0003ff00) need++; // top declet!=0, process 5
      }
    } //msd=0

  decDigitsFromDPD(dn, sourar, need);   // process declets
  return dn;
  }
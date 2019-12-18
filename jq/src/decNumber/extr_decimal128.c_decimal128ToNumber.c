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
typedef  TYPE_1__ decimal128 ;
struct TYPE_9__ {scalar_t__ exponent; int /*<<< orphan*/  bits; } ;
typedef  TYPE_2__ decNumber ;
typedef  int Int ;

/* Variables and functions */
 size_t* COMBEXP ; 
 size_t* COMBMSD ; 
 scalar_t__ DECIMAL128_Bias ; 
 int /*<<< orphan*/  DECINF ; 
 scalar_t__ DECLITEND ; 
 int /*<<< orphan*/  DECNAN ; 
 int /*<<< orphan*/  DECNEG ; 
 int /*<<< orphan*/  DECSNAN ; 
 void* UBTOUI (scalar_t__) ; 
 int /*<<< orphan*/  decDigitsFromDPD (TYPE_2__*,size_t*,int) ; 
 int /*<<< orphan*/  decNumberZero (TYPE_2__*) ; 
 int sourhi ; 
 void* sourlo ; 
 void* sourmh ; 
 void* sourml ; 

decNumber * decimal128ToNumber(const decimal128 *d128, decNumber *dn) {
  uInt msd;                        // coefficient MSD
  uInt exp;                        // exponent top two bits
  uInt comb;                       // combination field
  Int  need;                       // work
  uInt uiwork;                     // for macros
  uInt sourar[4];                  // source 128-bit
  #define sourhi sourar[3]         // name the word with the sign
  #define sourmh sourar[2]         // and the mid-high word
  #define sourml sourar[1]         // and the mod-low word
  #define sourlo sourar[0]         // and the lowest word

  // load source from storage; this is endian
  if (DECLITEND) {
    sourlo=UBTOUI(d128->bytes   ); // directly load the low int
    sourml=UBTOUI(d128->bytes+4 ); // then the mid-low
    sourmh=UBTOUI(d128->bytes+8 ); // then the mid-high
    sourhi=UBTOUI(d128->bytes+12); // then the high int
    }
   else {
    sourhi=UBTOUI(d128->bytes   ); // directly load the high int
    sourmh=UBTOUI(d128->bytes+4 ); // then the mid-high
    sourml=UBTOUI(d128->bytes+8 ); // then the mid-low
    sourlo=UBTOUI(d128->bytes+12); // then the low int
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
    dn->exponent=(exp<<12)+((sourhi>>14)&0xfff)-DECIMAL128_Bias; // unbiased
    }

  // get the coefficient
  sourhi&=0x00003fff;              // clean coefficient continuation
  if (msd) {                       // non-zero msd
    sourhi|=msd<<14;               // prefix to coefficient
    need=12;                       // process 12 declets
    }
   else { // msd=0
    if (sourhi) need=11;           // declets to process
     else if (sourmh) need=10;
     else if (sourml) need=7;
     else if (sourlo) need=4;
     else return dn;               // easy: coefficient is 0
    } //msd=0

  decDigitsFromDPD(dn, sourar, need);   // process declets
  // decNumberShow(dn);
  return dn;
  }
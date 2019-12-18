#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t digits; size_t exponent; size_t* lsu; } ;
typedef  TYPE_1__ decNumber ;
typedef  size_t Unit ;
typedef  size_t Int ;
typedef  scalar_t__ Flag ;

/* Variables and functions */
 size_t BADINT ; 
 size_t BIGEVEN ; 
 size_t BIGODD ; 
 size_t DECDPUN ; 
 scalar_t__ ISZERO (TYPE_1__ const*) ; 
 size_t QUOT10 (size_t const,size_t) ; 
 scalar_t__ decNumberIsNegative (TYPE_1__ const*) ; 
 size_t* powers ; 

__attribute__((used)) static Int decGetInt(const decNumber *dn) {
  Int  theInt;                          // result accumulator
  const Unit *up;                       // work
  Int  got;                             // digits (real or not) processed
  Int  ilength=dn->digits+dn->exponent; // integral length
  Flag neg=decNumberIsNegative(dn);     // 1 if -ve

  // The number must be an integer that fits in 10 digits
  // Assert, here, that 10 is enough for any rescale Etiny
  #if DEC_MAX_EMAX > 999999999
    #error GetInt may need updating [for Emax]
  #endif
  #if DEC_MIN_EMIN < -999999999
    #error GetInt may need updating [for Emin]
  #endif
  if (ISZERO(dn)) return 0;             // zeros are OK, with any exponent

  up=dn->lsu;                           // ready for lsu
  theInt=0;                             // ready to accumulate
  if (dn->exponent>=0) {                // relatively easy
    // no fractional part [usual]; allow for positive exponent
    got=dn->exponent;
    }
   else { // -ve exponent; some fractional part to check and discard
    Int count=-dn->exponent;            // digits to discard
    // spin up whole units until reach the Unit with the unit digit
    for (; count>=DECDPUN; up++) {
      if (*up!=0) return BADINT;        // non-zero Unit to discard
      count-=DECDPUN;
      }
    if (count==0) got=0;                // [a multiple of DECDPUN]
     else {                             // [not multiple of DECDPUN]
      Int rem;                          // work
      // slice off fraction digits and check for non-zero
      #if DECDPUN<=4
        theInt=QUOT10(*up, count);
        rem=*up-theInt*powers[count];
      #else
        rem=*up%powers[count];          // slice off discards
        theInt=*up/powers[count];
      #endif
      if (rem!=0) return BADINT;        // non-zero fraction
      // it looks good
      got=DECDPUN-count;                // number of digits so far
      up++;                             // ready for next
      }
    }
  // now it's known there's no fractional part

  // tricky code now, to accumulate up to 9.3 digits
  if (got==0) {theInt=*up; got+=DECDPUN; up++;} // ensure lsu is there

  if (ilength<11) {
    Int save=theInt;
    // collect any remaining unit(s)
    for (; got<ilength; up++) {
      theInt+=*up*powers[got];
      got+=DECDPUN;
      }
    if (ilength==10) {                  // need to check for wrap
      if (theInt/(Int)powers[got-DECDPUN]!=(Int)*(up-1)) ilength=11;
         // [that test also disallows the BADINT result case]
       else if (neg && theInt>1999999997) ilength=11;
       else if (!neg && theInt>999999999) ilength=11;
      if (ilength==11) theInt=save;     // restore correct low bit
      }
    }

  if (ilength>10) {                     // too big
    if (theInt&1) return BIGODD;        // bottom bit 1
    return BIGEVEN;                     // bottom bit 0
    }

  if (neg) theInt=-theInt;              // apply sign
  return theInt;
  }
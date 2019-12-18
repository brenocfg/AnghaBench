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
typedef  int uInt ;
typedef  int uByte ;
struct TYPE_5__ {int digits; int exponent; int /*<<< orphan*/  bits; scalar_t__* lsu; } ;
typedef  TYPE_1__ decNumber ;
typedef  scalar_t__ Unit ;
typedef  int Int ;

/* Variables and functions */
 int DECDPUN ; 
 int /*<<< orphan*/  DECNEG ; 
 int const DECNUMMAXE ; 
 int DECPMINUS ; 
 int DECPMINUSALT ; 
 int* DECPOWERS ; 
 int /*<<< orphan*/  decNumberZero (TYPE_1__*) ; 

decNumber * decPackedToNumber(const uByte *bcd, Int length,
                              const Int *scale, decNumber *dn) {
  const uByte *last=bcd+length-1;  // -> last byte
  const uByte *first;              // -> first non-zero byte
  uInt  nib;                       // work nibble
  Unit  *up=dn->lsu;               // output pointer
  Int   digits;                    // digits count
  Int   cut=0;                     // phase of output

  decNumberZero(dn);               // default result
  last=&bcd[length-1];
  nib=*last & 0x0f;                // get the sign
  if (nib==DECPMINUS || nib==DECPMINUSALT) dn->bits=DECNEG;
   else if (nib<=9) return NULL;   // not a sign nibble

  // skip leading zero bytes [final byte is always non-zero, due to sign]
  for (first=bcd; *first==0;) first++;
  digits=(last-first)*2+1;              // calculate digits ..
  if ((*first & 0xf0)==0) digits--;     // adjust for leading zero nibble
  if (digits!=0) dn->digits=digits;     // count of actual digits [if 0,
                                        // leave as 1]

  // check the adjusted exponent; note that scale could be unbounded
  dn->exponent=-*scale;                 // set the exponent
  if (*scale>=0) {                      // usual case
    if ((dn->digits-*scale-1)<-DECNUMMAXE) {      // underflow
      decNumberZero(dn);
      return NULL;}
    }
   else { // -ve scale; +ve exponent
    // need to be careful to avoid wrap, here, also BADINT case
    if ((*scale<-DECNUMMAXE)            // overflow even without digits
         || ((dn->digits-*scale-1)>DECNUMMAXE)) { // overflow
      decNumberZero(dn);
      return NULL;}
    }
  if (digits==0) return dn;             // result was zero

  // copy the digits to the number's units, starting at the lsu
  // [unrolled]
  for (;;) {                            // forever
    // left nibble first
    nib=(unsigned)(*last & 0xf0)>>4;
    // got a digit, in nib
    if (nib>9) {decNumberZero(dn); return NULL;}

    if (cut==0) *up=(Unit)nib;
     else *up=(Unit)(*up+nib*DECPOWERS[cut]);
    digits--;
    if (digits==0) break;               // got them all
    cut++;
    if (cut==DECDPUN) {
      up++;
      cut=0;
      }
    last--;                             // ready for next
    nib=*last & 0x0f;                   // get right nibble
    if (nib>9) {decNumberZero(dn); return NULL;}

    // got a digit, in nib
    if (cut==0) *up=(Unit)nib;
     else *up=(Unit)(*up+nib*DECPOWERS[cut]);
    digits--;
    if (digits==0) break;               // got them all
    cut++;
    if (cut==DECDPUN) {
      up++;
      cut=0;
      }
    } // forever

  return dn;
  }
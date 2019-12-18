#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uInt ;
struct TYPE_17__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  digits; } ;
typedef  TYPE_1__ decNumber ;
typedef  int /*<<< orphan*/  decContext ;
typedef  int /*<<< orphan*/  bufb ;
typedef  int /*<<< orphan*/  bufa ;
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */
 int /*<<< orphan*/  COMPTOTAL ; 
 int D2N (int /*<<< orphan*/ ) ; 
 int D2U (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECBUFFER ; 
 int /*<<< orphan*/  DECNEG ; 
 int DEC_Insufficient_storage ; 
 scalar_t__ decCheckOperands (TYPE_1__*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decCompareOp (TYPE_1__*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  decNumberCopy (TYPE_1__*,TYPE_1__ const*) ; 
 scalar_t__ decNumberIsNegative (TYPE_1__ const*) ; 
 int /*<<< orphan*/  decStatus (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 

decNumber * decNumberCompareTotalMag(decNumber *res, const decNumber *lhs,
                                     const decNumber *rhs, decContext *set) {
  uInt status=0;                   // accumulator
  uInt needbytes;                  // for space calculations
  decNumber bufa[D2N(DECBUFFER+1)];// +1 in case DECBUFFER=0
  decNumber *allocbufa=NULL;       // -> allocated bufa, iff allocated
  decNumber bufb[D2N(DECBUFFER+1)];
  decNumber *allocbufb=NULL;       // -> allocated bufb, iff allocated
  decNumber *a, *b;                // temporary pointers

  #if DECCHECK
  if (decCheckOperands(res, lhs, rhs, set)) return res;
  #endif

  do {                                  // protect allocated storage
    // if either is negative, take a copy and absolute
    if (decNumberIsNegative(lhs)) {     // lhs<0
      a=bufa;
      needbytes=sizeof(decNumber)+(D2U(lhs->digits)-1)*sizeof(Unit);
      if (needbytes>sizeof(bufa)) {     // need malloc space
        allocbufa=(decNumber *)malloc(needbytes);
        if (allocbufa==NULL) {          // hopeless -- abandon
          status|=DEC_Insufficient_storage;
          break;}
        a=allocbufa;                    // use the allocated space
        }
      decNumberCopy(a, lhs);            // copy content
      a->bits&=~DECNEG;                 // .. and clear the sign
      lhs=a;                            // use copy from here on
      }
    if (decNumberIsNegative(rhs)) {     // rhs<0
      b=bufb;
      needbytes=sizeof(decNumber)+(D2U(rhs->digits)-1)*sizeof(Unit);
      if (needbytes>sizeof(bufb)) {     // need malloc space
        allocbufb=(decNumber *)malloc(needbytes);
        if (allocbufb==NULL) {          // hopeless -- abandon
          status|=DEC_Insufficient_storage;
          break;}
        b=allocbufb;                    // use the allocated space
        }
      decNumberCopy(b, rhs);            // copy content
      b->bits&=~DECNEG;                 // .. and clear the sign
      rhs=b;                            // use copy from here on
      }
    decCompareOp(res, lhs, rhs, set, COMPTOTAL, &status);
    } while(0);                         // end protected

  if (allocbufa!=NULL) free(allocbufa); // drop any storage used
  if (allocbufb!=NULL) free(allocbufb); // ..
  if (status!=0) decStatus(res, status, set);
  return res;
  }
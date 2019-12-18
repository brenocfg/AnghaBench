#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
typedef  int uInt ;
struct TYPE_31__ {int /*<<< orphan*/  bits; scalar_t__ digits; } ;
typedef  TYPE_1__ decNumber ;
struct TYPE_32__ {scalar_t__ digits; int /*<<< orphan*/  emin; int /*<<< orphan*/  emax; int /*<<< orphan*/  extended; } ;
typedef  TYPE_2__ decContext ;
typedef  int /*<<< orphan*/  bufa ;
typedef  int /*<<< orphan*/  Unit ;
typedef  int /*<<< orphan*/  LI ;

/* Variables and functions */
 int D2N (int) ; 
 int D2U (scalar_t__) ; 
 int DECBUFFER ; 
 int /*<<< orphan*/  DECNAN ; 
 TYPE_1__ const* DECUNUSED ; 
 int DEC_Insufficient_storage ; 
 int DEC_Invalid_operation ; 
 int /*<<< orphan*/  DEC_MAX_EMAX ; 
 int /*<<< orphan*/  DEC_MIN_EMIN ; 
 int DEC_sNaN ; 
 int /*<<< orphan*/  decAddOp (TYPE_1__*,TYPE_1__*,TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  decCheckInexact (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ decCheckMath (TYPE_1__ const*,TYPE_2__*,int*) ; 
 scalar_t__ decCheckOperands (TYPE_1__*,TYPE_1__ const*,TYPE_1__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  decMultiplyOp (TYPE_1__*,TYPE_1__ const*,TYPE_1__ const*,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  decNumberIsSpecial (TYPE_1__ const*) ; 
 int /*<<< orphan*/  decNumberZero (TYPE_1__*) ; 
 int /*<<< orphan*/  decStatus (TYPE_1__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 

decNumber * decNumberFMA(decNumber *res, const decNumber *lhs,
                         const decNumber *rhs, const decNumber *fhs,
                         decContext *set) {
  uInt status=0;                   // accumulator
  decContext dcmul;                // context for the multiplication
  uInt needbytes;                  // for space calculations
  decNumber bufa[D2N(DECBUFFER*2+1)];
  decNumber *allocbufa=NULL;       // -> allocated bufa, iff allocated
  decNumber *acc;                  // accumulator pointer
  decNumber dzero;                 // work

  #if DECCHECK
  if (decCheckOperands(res, lhs, rhs, set)) return res;
  if (decCheckOperands(res, fhs, DECUNUSED, set)) return res;
  #endif

  do {                                  // protect allocated storage
    #if DECSUBSET
    if (!set->extended) {               // [undefined if subset]
      status|=DEC_Invalid_operation;
      break;}
    #endif
    // Check math restrictions [these ensure no overflow or underflow]
    if ((!decNumberIsSpecial(lhs) && decCheckMath(lhs, set, &status))
     || (!decNumberIsSpecial(rhs) && decCheckMath(rhs, set, &status))
     || (!decNumberIsSpecial(fhs) && decCheckMath(fhs, set, &status))) break;
    // set up context for multiply
    dcmul=*set;
    dcmul.digits=lhs->digits+rhs->digits; // just enough
    // [The above may be an over-estimate for subset arithmetic, but that's OK]
    dcmul.emax=DEC_MAX_EMAX;            // effectively unbounded ..
    dcmul.emin=DEC_MIN_EMIN;            // [thanks to Math restrictions]
    // set up decNumber space to receive the result of the multiply
    acc=bufa;                           // may fit
    needbytes=sizeof(decNumber)+(D2U(dcmul.digits)-1)*sizeof(Unit);
    if (needbytes>sizeof(bufa)) {       // need malloc space
      allocbufa=(decNumber *)malloc(needbytes);
      if (allocbufa==NULL) {            // hopeless -- abandon
        status|=DEC_Insufficient_storage;
        break;}
      acc=allocbufa;                    // use the allocated space
      }
    // multiply with extended range and necessary precision
    //printf("emin=%ld\n", dcmul.emin);
    decMultiplyOp(acc, lhs, rhs, &dcmul, &status);
    // Only Invalid operation (from sNaN or Inf * 0) is possible in
    // status; if either is seen than ignore fhs (in case it is
    // another sNaN) and set acc to NaN unless we had an sNaN
    // [decMultiplyOp leaves that to caller]
    // Note sNaN has to go through addOp to shorten payload if
    // necessary
    if ((status&DEC_Invalid_operation)!=0) {
      if (!(status&DEC_sNaN)) {         // but be true invalid
        decNumberZero(res);             // acc not yet set
        res->bits=DECNAN;
        break;
        }
      decNumberZero(&dzero);            // make 0 (any non-NaN would do)
      fhs=&dzero;                       // use that
      }
    #if DECCHECK
     else { // multiply was OK
      if (status!=0) printf("Status=%08lx after FMA multiply\n", (LI)status);
      }
    #endif
    // add the third operand and result -> res, and all is done
    decAddOp(res, acc, fhs, set, 0, &status);
    } while(0);                         // end protected

  if (allocbufa!=NULL) free(allocbufa); // drop any storage used
  if (status!=0) decStatus(res, status, set);
  #if DECCHECK
  decCheckInexact(res, set);
  #endif
  return res;
  }
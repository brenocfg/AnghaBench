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
typedef  int /*<<< orphan*/  accbuff ;
typedef  scalar_t__ Unit ;
typedef  scalar_t__ Int ;

/* Variables and functions */
 scalar_t__ BADINT ; 
 scalar_t__ D2U (scalar_t__) ; 
 int DECBUFFER ; 
 scalar_t__ DECDPUN ; 
 int SD2U (int) ; 
 scalar_t__ decUnitAddSub (scalar_t__ const*,scalar_t__,scalar_t__ const*,scalar_t__,scalar_t__,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 scalar_t__* powers ; 

__attribute__((used)) static Int decUnitCompare(const Unit *a, Int alength,
                          const Unit *b, Int blength, Int exp) {
  Unit  *acc;                      // accumulator for result
  Unit  accbuff[SD2U(DECBUFFER*2+1)]; // local buffer
  Unit  *allocacc=NULL;            // -> allocated acc buffer, iff allocated
  Int   accunits, need;            // units in use or needed for acc
  const Unit *l, *r, *u;           // work
  Int   expunits, exprem, result;  // ..

  if (exp==0) {                    // aligned; fastpath
    if (alength>blength) return 1;
    if (alength<blength) return -1;
    // same number of units in both -- need unit-by-unit compare
    l=a+alength-1;
    r=b+alength-1;
    for (;l>=a; l--, r--) {
      if (*l>*r) return 1;
      if (*l<*r) return -1;
      }
    return 0;                      // all units match
    } // aligned

  // Unaligned.  If one is >1 unit longer than the other, padded
  // approximately, then can return easily
  if (alength>blength+(Int)D2U(exp)) return 1;
  if (alength+1<blength+(Int)D2U(exp)) return -1;

  // Need to do a real subtract.  For this, a result buffer is needed
  // even though only the sign is of interest.  Its length needs
  // to be the larger of alength and padded blength, +2
  need=blength+D2U(exp);                // maximum real length of B
  if (need<alength) need=alength;
  need+=2;
  acc=accbuff;                          // assume use local buffer
  if (need*sizeof(Unit)>sizeof(accbuff)) {
    allocacc=(Unit *)malloc(need*sizeof(Unit));
    if (allocacc==NULL) return BADINT;  // hopeless -- abandon
    acc=allocacc;
    }
  // Calculate units and remainder from exponent.
  expunits=exp/DECDPUN;
  exprem=exp%DECDPUN;
  // subtract [A+B*(-m)]
  accunits=decUnitAddSub(a, alength, b, blength, expunits, acc,
                         -(Int)powers[exprem]);
  // [UnitAddSub result may have leading zeros, even on zero]
  if (accunits<0) result=-1;            // negative result
   else {                               // non-negative result
    // check units of the result before freeing any storage
    for (u=acc; u<acc+accunits-1 && *u==0;) u++;
    result=(*u==0 ? 0 : +1);
    }
  // clean up and return the result
  if (allocacc!=NULL) free(allocacc);   // drop any storage used
  return result;
  }
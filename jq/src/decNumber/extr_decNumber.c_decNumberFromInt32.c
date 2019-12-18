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
struct TYPE_5__ {int /*<<< orphan*/  bits; } ;
typedef  TYPE_1__ decNumber ;
typedef  int Int ;

/* Variables and functions */
 int BADINT ; 
 int /*<<< orphan*/  DECNEG ; 
 int /*<<< orphan*/  decNumberFromUInt32 (TYPE_1__*,int) ; 

decNumber * decNumberFromInt32(decNumber *dn, Int in) {
  uInt unsig;
  if (in>=0) unsig=in;
   else {                               // negative (possibly BADINT)
    if (in==BADINT) unsig=(uInt)1073741824*2; // special case
     else unsig=-in;                    // invert
    }
  // in is now positive
  decNumberFromUInt32(dn, unsig);
  if (in<0) dn->bits=DECNEG;            // sign needed
  return dn;
  }
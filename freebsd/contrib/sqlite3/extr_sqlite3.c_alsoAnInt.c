#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  double i64 ;
struct TYPE_3__ {int /*<<< orphan*/  enc; int /*<<< orphan*/  n; int /*<<< orphan*/  z; } ;
typedef  TYPE_1__ Mem ;

/* Variables and functions */
 scalar_t__ sqlite3Atoi64 (int /*<<< orphan*/ ,double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3RealSameAsInt (double,double) ; 

__attribute__((used)) static int alsoAnInt(Mem *pRec, double rValue, i64 *piValue){
  i64 iValue = (double)rValue;
  if( sqlite3RealSameAsInt(rValue,iValue) ){
    *piValue = iValue;
    return 1;
  }
  return 0==sqlite3Atoi64(pRec->z, piValue, pRec->n, pRec->enc);
}
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
typedef  scalar_t__ uInt ;
struct TYPE_5__ {scalar_t__* lsu; int /*<<< orphan*/  digits; } ;
typedef  TYPE_1__ decNumber ;
typedef  scalar_t__ Unit ;

/* Variables and functions */
 int DECDPUNMAX ; 
 int /*<<< orphan*/  decGetDigits (scalar_t__*,int) ; 
 int /*<<< orphan*/  decNumberZero (TYPE_1__*) ; 

decNumber * decNumberFromUInt32(decNumber *dn, uInt uin) {
  Unit *up;                             // work pointer
  decNumberZero(dn);                    // clean
  if (uin==0) return dn;                // [or decGetDigits bad call]
  for (up=dn->lsu; uin>0; up++) {
    *up=(Unit)(uin%(DECDPUNMAX+1));
    uin=uin/(DECDPUNMAX+1);
    }
  dn->digits=decGetDigits(dn->lsu, up-dn->lsu);
  return dn;
  }
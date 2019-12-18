#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t digits; scalar_t__* lsu; } ;
typedef  TYPE_1__ decNumber ;
typedef  scalar_t__ Unit ;
typedef  int /*<<< orphan*/  LI ;
typedef  size_t Int ;

/* Variables and functions */
 int D2U (size_t) ; 
 size_t DECDPUN ; 
 size_t MSUDIGITS (size_t) ; 
 size_t decGetDigits (scalar_t__*,int) ; 
 scalar_t__* powers ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static decNumber *decDecap(decNumber *dn, Int drop) {
  Unit *msu;                            // -> target cut point
  Int cut;                              // work
  if (drop>=dn->digits) {               // losing the whole thing
    #if DECCHECK
    if (drop>dn->digits)
      printf("decDecap called with drop>digits [%ld>%ld]\n",
             (LI)drop, (LI)dn->digits);
    #endif
    dn->lsu[0]=0;
    dn->digits=1;
    return dn;
    }
  msu=dn->lsu+D2U(dn->digits-drop)-1;   // -> likely msu
  cut=MSUDIGITS(dn->digits-drop);       // digits to be in use in msu
  if (cut!=DECDPUN) *msu%=powers[cut];  // clear left digits
  // that may have left leading zero digits, so do a proper count...
  dn->digits=decGetDigits(dn->lsu, msu-dn->lsu+1);
  return dn;
  }
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
typedef  int uInt ;
typedef  int /*<<< orphan*/  decFloat ;

/* Variables and functions */
 scalar_t__ CANONDPDOFF (int,int) ; 
 scalar_t__ CANONDPDTWO (int,int,int) ; 
 scalar_t__ DFISCCZERO (int /*<<< orphan*/  const*) ; 
 scalar_t__ DFISINF (int /*<<< orphan*/  const*) ; 
 scalar_t__ DFISSPECIAL (int /*<<< orphan*/  const*) ; 
 int DFWORD (int /*<<< orphan*/  const*,int) ; 
 int ECONMASK ; 
 int ECONNANMASK ; 

uInt decFloatIsCanonical(const decFloat *df) {
  if (DFISSPECIAL(df)) {
    if (DFISINF(df)) {
      if (DFWORD(df, 0)&ECONMASK) return 0;  // exponent continuation
      if (!DFISCCZERO(df)) return 0;         // coefficient continuation
      return 1;
      }
    // is a NaN
    if (DFWORD(df, 0)&ECONNANMASK) return 0; // exponent continuation
    if (DFISCCZERO(df)) return 1;            // coefficient continuation
    // drop through to check payload
    }
  { // declare block
  #if DOUBLE
    uInt sourhi=DFWORD(df, 0);
    uInt sourlo=DFWORD(df, 1);
    if (CANONDPDOFF(sourhi, 8)
     && CANONDPDTWO(sourhi, sourlo, 30)
     && CANONDPDOFF(sourlo, 20)
     && CANONDPDOFF(sourlo, 10)
     && CANONDPDOFF(sourlo, 0)) return 1;
  #elif QUAD
    uInt sourhi=DFWORD(df, 0);
    uInt sourmh=DFWORD(df, 1);
    uInt sourml=DFWORD(df, 2);
    uInt sourlo=DFWORD(df, 3);
    if (CANONDPDOFF(sourhi, 4)
     && CANONDPDTWO(sourhi, sourmh, 26)
     && CANONDPDOFF(sourmh, 16)
     && CANONDPDOFF(sourmh, 6)
     && CANONDPDTWO(sourmh, sourml, 28)
     && CANONDPDOFF(sourml, 18)
     && CANONDPDOFF(sourml, 8)
     && CANONDPDTWO(sourml, sourlo, 30)
     && CANONDPDOFF(sourlo, 20)
     && CANONDPDOFF(sourlo, 10)
     && CANONDPDOFF(sourlo, 0)) return 1;
  #endif
  } // block
  return 0;    // a declet is non-canonical
  }
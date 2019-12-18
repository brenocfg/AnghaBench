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
 scalar_t__* DECCOMBMSD ; 
 int DECPMAX ; 
 scalar_t__ DFISINF (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DFISNAN (int /*<<< orphan*/  const*) ; 
 int DFWORD (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  dpdlenchk (int,int) ; 
 int /*<<< orphan*/  dpdlendun (int,int) ; 

uInt decFloatDigits(const decFloat *df) {
  uInt dpd;                        // work
  uInt sourhi=DFWORD(df, 0);       // top word from source decFloat
  #if QUAD
  uInt sourmh, sourml;
  #endif
  uInt sourlo;

  if (DFISINF(df)) return 1;
  // A NaN effectively has an MSD of 0; otherwise if non-zero MSD
  // then the coefficient is full-length
  if (!DFISNAN(df) && DECCOMBMSD[sourhi>>26]) return DECPMAX;

  #if DOUBLE
    if (sourhi&0x0003ffff) {     // ends in first
      dpdlenchk(0, sourhi>>8);
      sourlo=DFWORD(df, 1);
      dpdlendun(1, (sourhi<<2) | (sourlo>>30));
      } // [cannot drop through]
    sourlo=DFWORD(df, 1);  // sourhi not involved now
    if (sourlo&0xfff00000) {     // in one of first two
      dpdlenchk(1, sourlo>>30);  // very rare
      dpdlendun(2, sourlo>>20);
      } // [cannot drop through]
    dpdlenchk(3, sourlo>>10);
    dpdlendun(4, sourlo);
    // [cannot drop through]

  #elif QUAD
    if (sourhi&0x00003fff) {     // ends in first
      dpdlenchk(0, sourhi>>4);
      sourmh=DFWORD(df, 1);
      dpdlendun(1, ((sourhi)<<6) | (sourmh>>26));
      } // [cannot drop through]
    sourmh=DFWORD(df, 1);
    if (sourmh) {
      dpdlenchk(1, sourmh>>26);
      dpdlenchk(2, sourmh>>16);
      dpdlenchk(3, sourmh>>6);
      sourml=DFWORD(df, 2);
      dpdlendun(4, ((sourmh)<<4) | (sourml>>28));
      } // [cannot drop through]
    sourml=DFWORD(df, 2);
    if (sourml) {
      dpdlenchk(4, sourml>>28);
      dpdlenchk(5, sourml>>18);
      dpdlenchk(6, sourml>>8);
      sourlo=DFWORD(df, 3);
      dpdlendun(7, ((sourml)<<2) | (sourlo>>30));
      } // [cannot drop through]
    sourlo=DFWORD(df, 3);
    if (sourlo&0xfff00000) {     // in one of first two
      dpdlenchk(7, sourlo>>30);  // very rare
      dpdlendun(8, sourlo>>20);
      } // [cannot drop through]
    dpdlenchk(9, sourlo>>10);
    dpdlendun(10, sourlo);
    // [cannot drop through]
  #endif
  }
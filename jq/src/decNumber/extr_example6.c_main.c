#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yearspack ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  startpack ;
typedef  int /*<<< orphan*/  respack ;
typedef  int /*<<< orphan*/  ratepack ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  decNumber ;
struct TYPE_9__ {int digits; scalar_t__ traps; } ;
typedef  TYPE_1__ decContext ;

/* Variables and functions */
 int /*<<< orphan*/  DEC_INIT_BASE ; 
 int /*<<< orphan*/  decContextDefault (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decNumberAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  decNumberDivide (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  decNumberFromString (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  decNumberMultiply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  decNumberPower (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  decNumberRescale (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  decPackedFromNumber (int*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decPackedToNumber (int*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int main(int argc, char *argv[]) {
  { // excerpt for User's Guide starts here--------------------------|
  decNumber one, mtwo, hundred;                   // constants
  decNumber start, rate, years;                   // parameters
  decNumber total;                                // result
  decContext set;                                 // working context

  uint8_t startpack[]={0x01, 0x00, 0x00, 0x0C};   // investment=100000
  int32_t startscale=0;
  uint8_t ratepack[]={0x06, 0x5C};                // rate=6.5%
  int32_t ratescale=1;
  uint8_t yearspack[]={0x02, 0x0C};               // years=20
  int32_t yearsscale=0;
  uint8_t respack[16];                            // result, packed
  int32_t resscale;                               // ..
  char  hexes[49];                                // for packed->hex
  int   i;                                        // counter

  if (argc<0) printf("%s", argv[1]);              // noop for warning

  decContextDefault(&set, DEC_INIT_BASE);         // initialize
  set.traps=0;                                    // no traps
  set.digits=25;                                  // precision 25
  decNumberFromString(&one,       "1", &set);     // set constants
  decNumberFromString(&mtwo,     "-2", &set);
  decNumberFromString(&hundred, "100", &set);

  decPackedToNumber(startpack, sizeof(startpack), &startscale, &start);
  decPackedToNumber(ratepack,  sizeof(ratepack),  &ratescale,  &rate);
  decPackedToNumber(yearspack, sizeof(yearspack), &yearsscale, &years);

  decNumberDivide(&rate, &rate, &hundred, &set);  // rate=rate/100
  decNumberAdd(&rate, &rate, &one, &set);         // rate=rate+1
  decNumberPower(&rate, &rate, &years, &set);     // rate=rate^years
  decNumberMultiply(&total, &rate, &start, &set); // total=rate*start
  decNumberRescale(&total, &total, &mtwo, &set);  // two digits please

  decPackedFromNumber(respack, sizeof(respack), &resscale, &total);

  // lay out the total as sixteen hexadecimal pairs
  for (i=0; i<16; i++) {
    sprintf(&hexes[i*3], "%02x ", respack[i]);
    }
  printf("Result: %s (scale=%ld)\n", hexes, (long int)resscale);

  } //---------------------------------------------------------------|
  return 0;
  }
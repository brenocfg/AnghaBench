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
typedef  int /*<<< orphan*/  decQuad ;
typedef  int /*<<< orphan*/  decNumber ;
typedef  int /*<<< orphan*/  decContext ;

/* Variables and functions */
 int DECQUAD_String ; 
 int /*<<< orphan*/  DEC_INIT_DECQUAD ; 
 int /*<<< orphan*/  decContextDefault (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decNumberFromString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decNumberPower (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decQuadAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decQuadFromNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decQuadFromString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decQuadToNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decQuadToString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, char *argv[]) {
  decQuad a;                       // working decQuad
  decNumber numa, numb;            // working decNumbers
  decContext set;                  // working context
  char string[DECQUAD_String];     // number->string buffer

  if (argc<3) {                    // not enough words
    printf("Please supply two numbers for power(2*a, b).\n");
    return 1;
    }
  decContextDefault(&set, DEC_INIT_DECQUAD); // initialize

  decQuadFromString(&a, argv[1], &set);      // get a
  decQuadAdd(&a, &a, &a, &set);              // double a
  decQuadToNumber(&a, &numa);                // convert to decNumber
  decNumberFromString(&numb, argv[2], &set);
  decNumberPower(&numa, &numa, &numb, &set); // numa=numa**numb
  decQuadFromNumber(&a, &numa, &set);        // back via a Quad
  decQuadToString(&a, string);               // ..

  printf("power(2*%s, %s) => %s\n", argv[1], argv[2], string);
  return 0;
  }
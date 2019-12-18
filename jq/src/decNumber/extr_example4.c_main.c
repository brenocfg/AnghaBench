#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  decNumber ;
struct TYPE_6__ {int /*<<< orphan*/  digits; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ decContext ;

/* Variables and functions */
 int /*<<< orphan*/  DECNUMDIGITS ; 
 int /*<<< orphan*/  DEC_Errors ; 
 int /*<<< orphan*/  DEC_INIT_BASE ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  decContextDefault (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* decContextStatusToString (TYPE_1__*) ; 
 int /*<<< orphan*/  decNumberAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  decNumberFromString (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  decNumberToString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  preserve ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signalHandler ; 

int main(int argc, char *argv[]) {
  decNumber a, b;                  // working numbers
  decContext set;                  // working context
  char string[DECNUMDIGITS+14];    // conversion buffer
  int value;                       // work variable

  if (argc<3) {                    // not enough words
    printf("Please supply two numbers to add.\n");
    return 1;
    }
  decContextDefault(&set, DEC_INIT_BASE);    // initialize

// [snip...
  signal(SIGFPE, signalHandler);   // set up signal handler
  value=setjmp(preserve);          // preserve and test environment
  if (value) {                     // (non-0 after longjmp)
    set.status &= DEC_Errors;      // keep only errors
    printf("Signal trapped [%s].\n", decContextStatusToString(&set));
    return 1;
    }
// ...snip]

// [change from Example 1, here]
  // leave traps enabled
  set.digits=DECNUMDIGITS;         // set precision

  decNumberFromString(&a, argv[1], &set);
  decNumberFromString(&b, argv[2], &set);

  decNumberAdd(&a, &a, &b, &set);            // A=A+B
  decNumberToString(&a, string);

  printf("%s + %s => %s\n", argv[1], argv[2], string);
  return 0;
  }
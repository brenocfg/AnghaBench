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
struct TYPE_4__ {int* bytes; } ;
typedef  TYPE_1__ decimal64 ;
typedef  int /*<<< orphan*/  decNumber ;
typedef  int /*<<< orphan*/  decContext ;

/* Variables and functions */
 int DECIMAL64_String ; 
 int /*<<< orphan*/  DEC_INIT_DECIMAL64 ; 
 int /*<<< orphan*/  decContextDefault (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decNumberToString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  decimal64FromString (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decimal64ToNumber (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int main(int argc, char *argv[]) {
  decimal64 a;                     // working decimal64 number
  decNumber d;                     // working number
  decContext set;                  // working context
  char string[DECIMAL64_String];   // number->string buffer
  char hexes[25];                  // decimal64->hex buffer
  int i;                           // counter

  if (argc<2) {                    // not enough words
    printf("Please supply a number.\n");
    return 1;
    }
  decContextDefault(&set, DEC_INIT_DECIMAL64); // initialize

  decimal64FromString(&a, argv[1], &set);
  // lay out the decimal64 as eight hexadecimal pairs
  for (i=0; i<8; i++) {
    sprintf(&hexes[i*3], "%02x ", a.bytes[i]);
    }
  decimal64ToNumber(&a, &d);
  decNumberToString(&d, string);
  printf("%s => %s=> %s\n", argv[1], hexes, string);
  return 0;
  }
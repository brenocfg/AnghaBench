#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  exp; scalar_t__ sign; } ;
typedef  TYPE_1__ float80 ;

/* Variables and functions */
 TYPE_1__ F80_NAN ; 
 int /*<<< orphan*/  bias (int) ; 
 TYPE_1__ f80_add (TYPE_1__,TYPE_1__) ; 
 TYPE_1__ f80_div (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  f80_eq (TYPE_1__,TYPE_1__) ; 
 TYPE_1__ f80_from_int (int) ; 
 scalar_t__ f80_isnan (TYPE_1__) ; 
 int unbias (int /*<<< orphan*/ ) ; 

float80 f80_sqrt(float80 x) {
    if (f80_isnan(x) || x.sign)
        return F80_NAN;
    // for a rough guess, just cut the exponent by 2
    float80 guess = x;
    guess.exp = bias(unbias(guess.exp) / 2);
    // now converge on the answer, using newton's method
    float80 old_guess;
    float80 two = f80_from_int(2);
    int i = 0;
    do {
        old_guess = guess;
        guess = f80_div(f80_add(guess, f80_div(x, guess)), two);
    } while (!f80_eq(guess, old_guess) && i++ < 100);
    return guess;
}
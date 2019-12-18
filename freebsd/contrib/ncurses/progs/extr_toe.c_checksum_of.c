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
struct TYPE_6__ {int /*<<< orphan*/ * Strings; scalar_t__* Numbers; scalar_t__* Booleans; int /*<<< orphan*/  term_names; } ;
typedef  TYPE_1__ TERMTYPE ;

/* Variables and functions */
 unsigned int NUM_BOOLEANS (TYPE_1__*) ; 
 unsigned int NUM_NUMBERS (TYPE_1__*) ; 
 unsigned int NUM_STRINGS (TYPE_1__*) ; 
 unsigned long string_sum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long
checksum_of(TERMTYPE *tp)
{
    unsigned long result = string_sum(tp->term_names);
    unsigned i;

    for (i = 0; i < NUM_BOOLEANS(tp); i++) {
	result += (unsigned long) (tp->Booleans[i]);
    }
    for (i = 0; i < NUM_NUMBERS(tp); i++) {
	result += (unsigned long) (tp->Numbers[i]);
    }
    for (i = 0; i < NUM_STRINGS(tp); i++) {
	result += string_sum(tp->Strings[i]);
    }
    return result;
}
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
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ok (int) ; 
 int should_use_h2 (int,int*) ; 

__attribute__((used)) static void test_should_use_h2(void)
{
    int8_t counter = -1;
    int i;
    for (i = 0; i != 110; ++i) {
        int use_h2 = should_use_h2(5, &counter);
        switch (counter) {
        case 0:
        case 20:
        case 40:
        case 60:
        case 80:
            ok(use_h2 == 1);
            break;
        default:
            ok(use_h2 == 0);
            break;
        }
    }

    counter = 0;
    for (i = 0; i != 110; ++i) {
        int use_h2 = should_use_h2(7, &counter);
        switch (counter) {
        case 0:
        case 15:
        case 29:
        case 43:
        case 58:
        case 72:
        case 86:
            ok(use_h2 == 1);
            break;
        default:
            ok(use_h2 == 0);
            break;
        }
    }

    counter = 0;
    for (i = 0; i != 110; ++i) {
        int use_h2 = should_use_h2(93, &counter);
        switch (counter) {
        case 1:
        case 15:
        case 29:
        case 43:
        case 58:
        case 72:
        case 86:
            ok(use_h2 == 0);
            break;
        default:
            ok(use_h2 == 1);
            break;
        }
    }

    counter = 0;
    for (i = 0; i != 110; ++i) {
        int use_h2 = should_use_h2(0, &counter);
        ok(use_h2 == 0);
    }

    counter = 0;
    for (i = 0; i != 110; ++i) {
        int use_h2 = should_use_h2(100, &counter);
        ok(use_h2 == 1);
    }
}
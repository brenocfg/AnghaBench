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

/* Variables and functions */
 int /*<<< orphan*/  nop () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main() {
    int loops = 100000000;
    printf("looping %d times\n", loops);
    for (int i = 0; i < loops; i++)
        nop();
    printf("done looping\n");
}
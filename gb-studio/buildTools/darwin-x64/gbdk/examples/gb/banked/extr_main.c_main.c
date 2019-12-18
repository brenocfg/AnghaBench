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
 int /*<<< orphan*/  bank2 (int) ; 
 int /*<<< orphan*/  puts (char*) ; 

int main(void)
{
    puts("Testing 1,2,3...");
    puts("Calling bank2()");
    bank2(3);
    puts("Back to main()");
    return 0;
}
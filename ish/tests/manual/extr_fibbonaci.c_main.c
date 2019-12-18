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
 int fib (unsigned long) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned long strtoul (char const*,int /*<<< orphan*/ *,int) ; 

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        printf("argc is %d\n", argc);
        printf("please specify a number to fibbonaci\n");
        return 1;
    }
    unsigned long n = strtoul(argv[1], NULL, 10);
    printf("%lu\n", fib(n));
    return 0;
}
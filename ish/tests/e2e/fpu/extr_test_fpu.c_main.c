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
 int /*<<< orphan*/  printf (char*,double) ; 

int main(void) {
    double a = 0.12;
    double b = 16.0;
    printf("%.2f\n", a + b);
    printf("%.2f\n", a - b);
    printf("%.2f\n", a * b);
    printf("%.2f\n", a / b);
    printf("%.2f\n", b / a);
    printf("%.2f\n", a + a / b + b);
    printf("%.2f\n", (a + a) / (b + b));
    return 0;
}
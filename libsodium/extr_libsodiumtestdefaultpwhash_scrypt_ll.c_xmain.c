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
 int /*<<< orphan*/  N1 ; 
 int /*<<< orphan*/  N2 ; 
 int /*<<< orphan*/  N3 ; 
 int /*<<< orphan*/  p1 ; 
 int /*<<< orphan*/  p2 ; 
 int /*<<< orphan*/  p3 ; 
 int /*<<< orphan*/  passwd1 ; 
 int /*<<< orphan*/  passwd2 ; 
 int /*<<< orphan*/  passwd3 ; 
 int /*<<< orphan*/  r1 ; 
 int /*<<< orphan*/  r2 ; 
 int /*<<< orphan*/  r3 ; 
 int /*<<< orphan*/  salt1 ; 
 int /*<<< orphan*/  salt2 ; 
 int /*<<< orphan*/  salt3 ; 
 int /*<<< orphan*/  tv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
main(void)
{
    tv(passwd1, salt1, N1, r1, p1);
    tv(passwd2, salt2, N2, r2, p2);
    tv(passwd3, salt3, N3, r3, p3);

    return 0;
}
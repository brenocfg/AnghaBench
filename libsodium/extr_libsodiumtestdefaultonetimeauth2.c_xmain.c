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
 int /*<<< orphan*/  a ; 
 int /*<<< orphan*/  c ; 
 int crypto_onetimeauth_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  rs ; 

int
main(void)
{
    printf("%d\n", crypto_onetimeauth_verify(a, c, 131, rs));
    return 0;
}
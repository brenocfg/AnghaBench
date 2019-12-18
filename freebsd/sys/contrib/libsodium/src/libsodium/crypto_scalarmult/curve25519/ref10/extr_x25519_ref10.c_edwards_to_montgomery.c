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
typedef  int /*<<< orphan*/  fe25519 ;

/* Variables and functions */
 int /*<<< orphan*/  fe25519_add (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fe25519_invert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_sub (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
edwards_to_montgomery(fe25519 montgomeryX, const fe25519 edwardsY, const fe25519 edwardsZ)
{
    fe25519 tempX;
    fe25519 tempZ;

    fe25519_add(tempX, edwardsZ, edwardsY);
    fe25519_sub(tempZ, edwardsZ, edwardsY);
    fe25519_invert(tempZ, tempZ);
    fe25519_mul(montgomeryX, tempX, tempZ);
}
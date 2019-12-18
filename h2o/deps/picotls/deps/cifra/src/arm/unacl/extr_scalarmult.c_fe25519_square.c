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
typedef  int /*<<< orphan*/  UN_512bitValue ;

/* Variables and functions */
 int /*<<< orphan*/  fe25519_reduceTo256Bits_asm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  square256 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
fe25519_square(
    fe25519*       result,
    const fe25519* in
)
{
    UN_512bitValue tmp;

    square256(&tmp, in);
    fe25519_reduceTo256Bits_asm(result,&tmp);
}
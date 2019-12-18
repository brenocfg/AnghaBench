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
typedef  int /*<<< orphan*/  largefelem ;
typedef  int /*<<< orphan*/  felem ;

/* Variables and functions */
 int /*<<< orphan*/  felem_mul (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_reduce (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void felem_mul_reduce(felem out, const felem in1, const felem in2)
{
    largefelem tmp;
    felem_mul(tmp, in1, in2);
    felem_reduce(out, tmp);
}
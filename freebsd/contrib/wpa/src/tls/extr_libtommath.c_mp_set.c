#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* dp; int used; } ;
typedef  TYPE_1__ mp_int ;
typedef  int mp_digit ;

/* Variables and functions */
 int MP_MASK ; 
 int /*<<< orphan*/  mp_zero (TYPE_1__*) ; 

__attribute__((used)) static void mp_set (mp_int * a, mp_digit b)
{
  mp_zero (a);
  a->dp[0] = b & MP_MASK;
  a->used  = (a->dp[0] != 0) ? 1 : 0;
}
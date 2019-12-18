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
typedef  int /*<<< orphan*/  u_long ;
struct number {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  BN_get_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normalize (struct number*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_long
get_ulong(struct number *n)
{

	normalize(n, 0);
	return (BN_get_word(n->number));
}
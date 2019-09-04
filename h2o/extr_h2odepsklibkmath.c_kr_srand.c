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
typedef  int /*<<< orphan*/  krint64_t ;
typedef  int /*<<< orphan*/  krand_t ;

/* Variables and functions */
 int /*<<< orphan*/  kr_srand0 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 

krand_t *kr_srand(krint64_t seed)
{
	krand_t *kr;
	kr = malloc(sizeof(krand_t));
	kr_srand0(seed, kr);
	return kr;
}
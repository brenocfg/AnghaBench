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
struct fuzz {scalar_t__ slen; int /*<<< orphan*/  seed; } ;

/* Variables and functions */
 scalar_t__ fuzz_len (struct fuzz*) ; 
 int /*<<< orphan*/  fuzz_ptr (struct fuzz*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
fuzz_matches_original(struct fuzz *fuzz)
{
	if (fuzz_len(fuzz) != fuzz->slen)
		return 0;
	return memcmp(fuzz_ptr(fuzz), fuzz->seed, fuzz->slen) == 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  newkey ;
struct TYPE_2__ {int /*<<< orphan*/  fs_key; int /*<<< orphan*/  fs_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORTUNA_LOCKED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int RANDOM_KEYSIZE ; 
 int /*<<< orphan*/  RANDOM_RESEED_ASSERT_LOCK_NOT_OWNED () ; 
 int /*<<< orphan*/  RANDOM_RESEED_LOCK () ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ fortuna_concurrent_read ; 
 TYPE_1__ fortuna_state ; 
 int /*<<< orphan*/  random_fortuna_genbytes (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random_fortuna_read_concurrent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uint128_is_zero (int /*<<< orphan*/ ) ; 

void
random_fortuna_read(uint8_t *buf, size_t bytecount)
{
	uint8_t newkey[RANDOM_KEYSIZE];

	if (fortuna_concurrent_read) {
		random_fortuna_read_concurrent(buf, bytecount, newkey);
		goto out;
	}

	RANDOM_RESEED_LOCK();
	KASSERT(!uint128_is_zero(fortuna_state.fs_counter), ("FS&K: C != 0"));

	random_fortuna_genbytes(buf, bytecount, newkey,
	    &fortuna_state.fs_counter, &fortuna_state.fs_key, FORTUNA_LOCKED);
	/* Returns unlocked */
	RANDOM_RESEED_ASSERT_LOCK_NOT_OWNED();

out:
	explicit_bzero(newkey, sizeof(newkey));
}
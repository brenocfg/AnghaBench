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
struct entropy_store {int entropy_count; int initialized; int /*<<< orphan*/  push_work; TYPE_1__* poolinfo; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int poolfracbits; int poolbitshift; int poolbytes; } ;

/* Variables and functions */
 int ENTROPY_BITS (struct entropy_store*) ; 
 int ENTROPY_SHIFT ; 
 int /*<<< orphan*/  POLL_IN ; 
 int READ_ONCE (int) ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 struct entropy_store blocking_pool ; 
 int cmpxchg (int*,int,int) ; 
 int crng_init ; 
 int /*<<< orphan*/  crng_reseed (int /*<<< orphan*/ *,struct entropy_store*) ; 
 int /*<<< orphan*/  fasync ; 
 struct entropy_store input_pool ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int min (int,int const) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  primary_crng ; 
 int /*<<< orphan*/  random_read_wait ; 
 int random_read_wakeup_bits ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_credit_entropy_bits (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  work_pending (int /*<<< orphan*/ *) ; 
 scalar_t__ wq_has_sleeper (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void credit_entropy_bits(struct entropy_store *r, int nbits)
{
	int entropy_count, orig, has_initialized = 0;
	const int pool_size = r->poolinfo->poolfracbits;
	int nfrac = nbits << ENTROPY_SHIFT;

	if (!nbits)
		return;

retry:
	entropy_count = orig = READ_ONCE(r->entropy_count);
	if (nfrac < 0) {
		/* Debit */
		entropy_count += nfrac;
	} else {
		/*
		 * Credit: we have to account for the possibility of
		 * overwriting already present entropy.	 Even in the
		 * ideal case of pure Shannon entropy, new contributions
		 * approach the full value asymptotically:
		 *
		 * entropy <- entropy + (pool_size - entropy) *
		 *	(1 - exp(-add_entropy/pool_size))
		 *
		 * For add_entropy <= pool_size/2 then
		 * (1 - exp(-add_entropy/pool_size)) >=
		 *    (add_entropy/pool_size)*0.7869...
		 * so we can approximate the exponential with
		 * 3/4*add_entropy/pool_size and still be on the
		 * safe side by adding at most pool_size/2 at a time.
		 *
		 * The use of pool_size-2 in the while statement is to
		 * prevent rounding artifacts from making the loop
		 * arbitrarily long; this limits the loop to log2(pool_size)*2
		 * turns no matter how large nbits is.
		 */
		int pnfrac = nfrac;
		const int s = r->poolinfo->poolbitshift + ENTROPY_SHIFT + 2;
		/* The +2 corresponds to the /4 in the denominator */

		do {
			unsigned int anfrac = min(pnfrac, pool_size/2);
			unsigned int add =
				((pool_size - entropy_count)*anfrac*3) >> s;

			entropy_count += add;
			pnfrac -= anfrac;
		} while (unlikely(entropy_count < pool_size-2 && pnfrac));
	}

	if (unlikely(entropy_count < 0)) {
		pr_warn("random: negative entropy/overflow: pool %s count %d\n",
			r->name, entropy_count);
		WARN_ON(1);
		entropy_count = 0;
	} else if (entropy_count > pool_size)
		entropy_count = pool_size;
	if ((r == &blocking_pool) && !r->initialized &&
	    (entropy_count >> ENTROPY_SHIFT) > 128)
		has_initialized = 1;
	if (cmpxchg(&r->entropy_count, orig, entropy_count) != orig)
		goto retry;

	if (has_initialized) {
		r->initialized = 1;
		wake_up_interruptible(&random_read_wait);
		kill_fasync(&fasync, SIGIO, POLL_IN);
	}

	trace_credit_entropy_bits(r->name, nbits,
				  entropy_count >> ENTROPY_SHIFT, _RET_IP_);

	if (r == &input_pool) {
		int entropy_bits = entropy_count >> ENTROPY_SHIFT;
		struct entropy_store *other = &blocking_pool;

		if (crng_init < 2) {
			if (entropy_bits < 128)
				return;
			crng_reseed(&primary_crng, r);
			entropy_bits = r->entropy_count >> ENTROPY_SHIFT;
		}

		/* initialize the blocking pool if necessary */
		if (entropy_bits >= random_read_wakeup_bits &&
		    !other->initialized) {
			schedule_work(&other->push_work);
			return;
		}

		/* should we wake readers? */
		if (entropy_bits >= random_read_wakeup_bits &&
		    wq_has_sleeper(&random_read_wait)) {
			wake_up_interruptible(&random_read_wait);
			kill_fasync(&fasync, SIGIO, POLL_IN);
		}
		/* If the input pool is getting full, and the blocking
		 * pool has room, send some entropy to the blocking
		 * pool.
		 */
		if (!work_pending(&other->push_work) &&
		    (ENTROPY_BITS(r) > 6 * r->poolinfo->poolbytes) &&
		    (ENTROPY_BITS(other) <= 6 * other->poolinfo->poolbytes))
			schedule_work(&other->push_work);
	}
}
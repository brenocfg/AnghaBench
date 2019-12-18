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
typedef  unsigned long u_int32_t ;
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_hex2bn (int /*<<< orphan*/ **,char*) ; 
 scalar_t__ BN_is_prime_ex (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_lshift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int BN_mod_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * BN_new () ; 
 scalar_t__ BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_rshift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 unsigned long MAXIMUM (unsigned long,unsigned long) ; 
 unsigned long MODULI_TESTS_COMPOSITE ; 
 unsigned long MODULI_TESTS_MILLER_RABIN ; 
#define  MODULI_TYPE_SAFE 133 
#define  MODULI_TYPE_SCHNORR 132 
#define  MODULI_TYPE_SOPHIE_GERMAIN 131 
#define  MODULI_TYPE_STRONG 130 
#define  MODULI_TYPE_UNKNOWN 129 
#define  MODULI_TYPE_UNSTRUCTURED 128 
 scalar_t__ QLINESIZE ; 
 unsigned long QSIZE_MINIMUM ; 
 unsigned long TRIAL_MINIMUM ; 
 unsigned long ULONG_MAX ; 
 unsigned long count_lines (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctime (scalar_t__*) ; 
 int /*<<< orphan*/  debug (char*,unsigned long,...) ; 
 int /*<<< orphan*/  debug2 (char*,...) ; 
 int /*<<< orphan*/  debug3 (char*,unsigned long) ; 
 int /*<<< orphan*/  error (char*,unsigned long) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/ * fgets (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  logit (char*,int /*<<< orphan*/ ,unsigned long,unsigned long,long) ; 
 int /*<<< orphan*/  print_progress (unsigned long,unsigned long,unsigned long) ; 
 scalar_t__ qfileout (int /*<<< orphan*/ *,int const,unsigned long,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ *) ; 
 unsigned long read_checkpoint (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strspn (char*,char*) ; 
 unsigned long strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  write_checkpoint (char*,unsigned long) ; 
 char* xmalloc (scalar_t__) ; 

int
prime_test(FILE *in, FILE *out, u_int32_t trials, u_int32_t generator_wanted,
    char *checkpoint_file, unsigned long start_lineno, unsigned long num_lines)
{
	BIGNUM *q, *p, *a;
	BN_CTX *ctx;
	char *cp, *lp;
	u_int32_t count_in = 0, count_out = 0, count_possible = 0;
	u_int32_t generator_known, in_tests, in_tries, in_type, in_size;
	unsigned long last_processed = 0, end_lineno;
	time_t time_start, time_stop;
	int res;

	if (trials < TRIAL_MINIMUM) {
		error("Minimum primality trials is %d", TRIAL_MINIMUM);
		return (-1);
	}

	if (num_lines == 0)
		end_lineno = count_lines(in);
	else
		end_lineno = start_lineno + num_lines;

	time(&time_start);

	if ((p = BN_new()) == NULL)
		fatal("BN_new failed");
	if ((q = BN_new()) == NULL)
		fatal("BN_new failed");
	if ((ctx = BN_CTX_new()) == NULL)
		fatal("BN_CTX_new failed");

	debug2("%.24s Final %u Miller-Rabin trials (%x generator)",
	    ctime(&time_start), trials, generator_wanted);

	if (checkpoint_file != NULL)
		last_processed = read_checkpoint(checkpoint_file);
	last_processed = start_lineno = MAXIMUM(last_processed, start_lineno);
	if (end_lineno == ULONG_MAX)
		debug("process from line %lu from pipe", last_processed);
	else
		debug("process from line %lu to line %lu", last_processed,
		    end_lineno);

	res = 0;
	lp = xmalloc(QLINESIZE + 1);
	while (fgets(lp, QLINESIZE + 1, in) != NULL && count_in < end_lineno) {
		count_in++;
		if (count_in <= last_processed) {
			debug3("skipping line %u, before checkpoint or "
			    "specified start line", count_in);
			continue;
		}
		if (checkpoint_file != NULL)
			write_checkpoint(checkpoint_file, count_in);
		print_progress(start_lineno, count_in, end_lineno);
		if (strlen(lp) < 14 || *lp == '!' || *lp == '#') {
			debug2("%10u: comment or short line", count_in);
			continue;
		}

		/* XXX - fragile parser */
		/* time */
		cp = &lp[14];	/* (skip) */

		/* type */
		in_type = strtoul(cp, &cp, 10);

		/* tests */
		in_tests = strtoul(cp, &cp, 10);

		if (in_tests & MODULI_TESTS_COMPOSITE) {
			debug2("%10u: known composite", count_in);
			continue;
		}

		/* tries */
		in_tries = strtoul(cp, &cp, 10);

		/* size (most significant bit) */
		in_size = strtoul(cp, &cp, 10);

		/* generator (hex) */
		generator_known = strtoul(cp, &cp, 16);

		/* Skip white space */
		cp += strspn(cp, " ");

		/* modulus (hex) */
		switch (in_type) {
		case MODULI_TYPE_SOPHIE_GERMAIN:
			debug2("%10u: (%u) Sophie-Germain", count_in, in_type);
			a = q;
			if (BN_hex2bn(&a, cp) == 0)
				fatal("BN_hex2bn failed");
			/* p = 2*q + 1 */
			if (BN_lshift(p, q, 1) == 0)
				fatal("BN_lshift failed");
			if (BN_add_word(p, 1) == 0)
				fatal("BN_add_word failed");
			in_size += 1;
			generator_known = 0;
			break;
		case MODULI_TYPE_UNSTRUCTURED:
		case MODULI_TYPE_SAFE:
		case MODULI_TYPE_SCHNORR:
		case MODULI_TYPE_STRONG:
		case MODULI_TYPE_UNKNOWN:
			debug2("%10u: (%u)", count_in, in_type);
			a = p;
			if (BN_hex2bn(&a, cp) == 0)
				fatal("BN_hex2bn failed");
			/* q = (p-1) / 2 */
			if (BN_rshift(q, p, 1) == 0)
				fatal("BN_rshift failed");
			break;
		default:
			debug2("Unknown prime type");
			break;
		}

		/*
		 * due to earlier inconsistencies in interpretation, check
		 * the proposed bit size.
		 */
		if ((u_int32_t)BN_num_bits(p) != (in_size + 1)) {
			debug2("%10u: bit size %u mismatch", count_in, in_size);
			continue;
		}
		if (in_size < QSIZE_MINIMUM) {
			debug2("%10u: bit size %u too short", count_in, in_size);
			continue;
		}

		if (in_tests & MODULI_TESTS_MILLER_RABIN)
			in_tries += trials;
		else
			in_tries = trials;

		/*
		 * guess unknown generator
		 */
		if (generator_known == 0) {
			if (BN_mod_word(p, 24) == 11)
				generator_known = 2;
			else if (BN_mod_word(p, 12) == 5)
				generator_known = 3;
			else {
				u_int32_t r = BN_mod_word(p, 10);

				if (r == 3 || r == 7)
					generator_known = 5;
			}
		}
		/*
		 * skip tests when desired generator doesn't match
		 */
		if (generator_wanted > 0 &&
		    generator_wanted != generator_known) {
			debug2("%10u: generator %d != %d",
			    count_in, generator_known, generator_wanted);
			continue;
		}

		/*
		 * Primes with no known generator are useless for DH, so
		 * skip those.
		 */
		if (generator_known == 0) {
			debug2("%10u: no known generator", count_in);
			continue;
		}

		count_possible++;

		/*
		 * The (1/4)^N performance bound on Miller-Rabin is
		 * extremely pessimistic, so don't spend a lot of time
		 * really verifying that q is prime until after we know
		 * that p is also prime. A single pass will weed out the
		 * vast majority of composite q's.
		 */
		if (BN_is_prime_ex(q, 1, ctx, NULL) <= 0) {
			debug("%10u: q failed first possible prime test",
			    count_in);
			continue;
		}

		/*
		 * q is possibly prime, so go ahead and really make sure
		 * that p is prime. If it is, then we can go back and do
		 * the same for q. If p is composite, chances are that
		 * will show up on the first Rabin-Miller iteration so it
		 * doesn't hurt to specify a high iteration count.
		 */
		if (!BN_is_prime_ex(p, trials, ctx, NULL)) {
			debug("%10u: p is not prime", count_in);
			continue;
		}
		debug("%10u: p is almost certainly prime", count_in);

		/* recheck q more rigorously */
		if (!BN_is_prime_ex(q, trials - 1, ctx, NULL)) {
			debug("%10u: q is not prime", count_in);
			continue;
		}
		debug("%10u: q is almost certainly prime", count_in);

		if (qfileout(out, MODULI_TYPE_SAFE,
		    in_tests | MODULI_TESTS_MILLER_RABIN,
		    in_tries, in_size, generator_known, p)) {
			res = -1;
			break;
		}

		count_out++;
	}

	time(&time_stop);
	free(lp);
	BN_free(p);
	BN_free(q);
	BN_CTX_free(ctx);

	if (checkpoint_file != NULL)
		unlink(checkpoint_file);

	logit("%.24s Found %u safe primes of %u candidates in %ld seconds",
	    ctime(&time_stop), count_out, count_possible,
	    (long) (time_stop - time_start));

	return (res);
}
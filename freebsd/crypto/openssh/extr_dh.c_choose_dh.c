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
struct dhgroup {int size; int /*<<< orphan*/  p; int /*<<< orphan*/  g; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DH ;

/* Variables and functions */
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ ) ; 
 int _PATH_DH_MODULI ; 
 int arc4random_uniform (int) ; 
 int /*<<< orphan*/ * dh_new_group (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dh_new_group_fallback (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logit (char*,int,...) ; 
 int /*<<< orphan*/  parse_prime (int,char*,struct dhgroup*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int strerror (int /*<<< orphan*/ ) ; 

DH *
choose_dh(int min, int wantbits, int max)
{
	FILE *f;
	char *line = NULL;
	size_t linesize = 0;
	int best, bestcount, which, linenum;
	struct dhgroup dhg;

	if ((f = fopen(_PATH_DH_MODULI, "r")) == NULL) {
		logit("WARNING: could not open %s (%s), using fixed modulus",
		    _PATH_DH_MODULI, strerror(errno));
		return (dh_new_group_fallback(max));
	}

	linenum = 0;
	best = bestcount = 0;
	while (getline(&line, &linesize, f) != -1) {
		linenum++;
		if (!parse_prime(linenum, line, &dhg))
			continue;
		BN_clear_free(dhg.g);
		BN_clear_free(dhg.p);

		if (dhg.size > max || dhg.size < min)
			continue;

		if ((dhg.size > wantbits && dhg.size < best) ||
		    (dhg.size > best && best < wantbits)) {
			best = dhg.size;
			bestcount = 0;
		}
		if (dhg.size == best)
			bestcount++;
	}
	free(line);
	line = NULL;
	linesize = 0;
	rewind(f);

	if (bestcount == 0) {
		fclose(f);
		logit("WARNING: no suitable primes in %s", _PATH_DH_MODULI);
		return (dh_new_group_fallback(max));
	}

	linenum = 0;
	which = arc4random_uniform(bestcount);
	while (getline(&line, &linesize, f) != -1) {
		if (!parse_prime(linenum, line, &dhg))
			continue;
		if ((dhg.size > max || dhg.size < min) ||
		    dhg.size != best ||
		    linenum++ != which) {
			BN_clear_free(dhg.g);
			BN_clear_free(dhg.p);
			continue;
		}
		break;
	}
	free(line);
	line = NULL;
	fclose(f);
	if (linenum != which+1) {
		logit("WARNING: line %d disappeared in %s, giving up",
		    which, _PATH_DH_MODULI);
		return (dh_new_group_fallback(max));
	}

	return (dh_new_group(dhg.g, dhg.p));
}
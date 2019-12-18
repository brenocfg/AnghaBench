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
typedef  int uint64_t ;

/* Variables and functions */
 int UINT16_MAX ; 
 int cores ; 
 int /*<<< orphan*/  free (char*) ; 
 int guest_ncpus ; 
 int m ; 
 int sockets ; 
 int sscanf (char*,char*,int*,int*) ; 
 char* strdup (char const*) ; 
 char* strsep (char**,char*) ; 
 int threads ; 

__attribute__((used)) static int
topology_parse(const char *opt)
{
	uint64_t ncpus;
	int c, chk, n, s, t, tmp;
	char *cp, *str;
	bool ns, scts;

	c = 1, n = 1, s = 1, t = 1;
	ns = false, scts = false;
	str = strdup(opt);
	if (str == NULL)
		goto out;

	while ((cp = strsep(&str, ",")) != NULL) {
		if (sscanf(cp, "%i%n", &tmp, &chk) == 1) {
			n = tmp;
			ns = true;
		} else if (sscanf(cp, "cpus=%i%n", &tmp, &chk) == 1) {
			n = tmp;
			ns = true;
		} else if (sscanf(cp, "sockets=%i%n", &tmp, &chk) == 1) {
			s = tmp;
			scts = true;
		} else if (sscanf(cp, "cores=%i%n", &tmp, &chk) == 1) {
			c = tmp;
			scts = true;
		} else if (sscanf(cp, "threads=%i%n", &tmp, &chk) == 1) {
			t = tmp;
			scts = true;
#ifdef notyet  /* Do not expose this until vmm.ko implements it */
		} else if (sscanf(cp, "maxcpus=%i%n", &tmp, &chk) == 1) {
			m = tmp;
#endif
		/* Skip the empty argument case from -c "" */
		} else if (cp[0] == '\0')
			continue;
		else
			goto out;
		/* Any trailing garbage causes an error */
		if (cp[chk] != '\0')
			goto out;
	}
	free(str);
	str = NULL;

	/*
	 * Range check 1 <= n <= UINT16_MAX all values
	 */
	if (n < 1 || s < 1 || c < 1 || t < 1 ||
	    n > UINT16_MAX || s > UINT16_MAX || c > UINT16_MAX  ||
	    t > UINT16_MAX)
		return (-1);

	/* If only the cpus was specified, use that as sockets */
	if (!scts)
		s = n;
	/*
	 * Compute sockets * cores * threads avoiding overflow
	 * The range check above insures these are 16 bit values
	 * If n was specified check it against computed ncpus
	 */
	ncpus = (uint64_t)s * c * t;
	if (ncpus > UINT16_MAX || (ns && n != ncpus))
		return (-1);

	guest_ncpus = ncpus;
	sockets = s;
	cores = c;
	threads = t;
	return(0);

out:
	free(str);
	return (-1);
}
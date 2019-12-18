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
typedef  int /*<<< orphan*/  u_char ;
struct moduledir {int d_hintsz; int /*<<< orphan*/  d_path; int /*<<< orphan*/ * d_hints; } ;
struct mod_depend {int md_ver_preferred; int md_ver_minimum; int md_ver_maximum; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_ALIGN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  MDT_VERSION 128 
 int /*<<< orphan*/  bcmp (int /*<<< orphan*/ *,char const*,int) ; 
 char* file_lookup (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kld_ext_list ; 
 int /*<<< orphan*/  moduledir_readhints (struct moduledir*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *
mod_search_hints(struct moduledir *mdp, const char *modname,
	struct mod_depend *verinfo)
{
	u_char	*cp, *recptr, *bufend, *best;
	char	*result;
	int		*intp, bestver, blen, clen, found, ival, modnamelen, reclen;

	moduledir_readhints(mdp);
	modnamelen = strlen(modname);
	found = 0;
	result = NULL;
	bestver = 0;
	if (mdp->d_hints == NULL)
		goto bad;
	recptr = mdp->d_hints;
	bufend = recptr + mdp->d_hintsz;
	clen = blen = 0;
	best = cp = NULL;
	while (recptr < bufend && !found) {
		intp = (int*)recptr;
		reclen = *intp++;
		ival = *intp++;
		cp = (u_char*)intp;
		switch (ival) {
		case MDT_VERSION:
			clen = *cp++;
			if (clen != modnamelen || bcmp(cp, modname, clen) != 0)
				break;
			cp += clen;
			INT_ALIGN(mdp->d_hints, cp);
			ival = *(int*)cp;
			cp += sizeof(int);
			clen = *cp++;
			if (verinfo == NULL || ival == verinfo->md_ver_preferred) {
				found = 1;
				break;
			}
			if (ival >= verinfo->md_ver_minimum &&
			  ival <= verinfo->md_ver_maximum &&
			  ival > bestver) {
				bestver = ival;
				best = cp;
				blen = clen;
			}
			break;
		default:
			break;
		}
		recptr += reclen + sizeof(int);
	}
	/*
	 * Finally check if KLD is in the place
	 */
	if (found)
		result = file_lookup(mdp->d_path, (const char *)cp, clen, NULL);
	else if (best)
		result = file_lookup(mdp->d_path, (const char *)best, blen, NULL);
bad:
	/*
	 * If nothing found or hints is absent - fallback to the old way
	 * by using "kldname[.ko]" as module name.
	 */
	if (!found && !bestver && result == NULL)
		result = file_lookup(mdp->d_path, modname, modnamelen, kld_ext_list);
	return result;
}
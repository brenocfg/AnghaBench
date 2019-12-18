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
struct ccdiinfo {int* ii_index; int ii_ndisk; int ii_startblk; int ii_startoff; } ;
struct ccdcinfo {int ci_size; } ;
struct ccd_s {int sc_ndisks; int sc_ileave; struct ccdcinfo* sc_cinfo; struct ccdiinfo* sc_itable; } ;
typedef  int daddr_t ;

/* Variables and functions */
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  g_free (int*) ; 
 void* g_malloc (int,int) ; 

__attribute__((used)) static void
ccdinterleave(struct ccd_s *cs)
{
	struct ccdcinfo *ci, *smallci;
	struct ccdiinfo *ii;
	daddr_t bn, lbn;
	int ix;
	daddr_t size;


	/*
	 * Allocate an interleave table.  The worst case occurs when each
	 * of N disks is of a different size, resulting in N interleave
	 * tables.
	 *
	 * Chances are this is too big, but we don't care.
	 */
	size = (cs->sc_ndisks + 1) * sizeof(struct ccdiinfo);
	cs->sc_itable = g_malloc(size, M_WAITOK | M_ZERO);

	/*
	 * Trivial case: no interleave (actually interleave of disk size).
	 * Each table entry represents a single component in its entirety.
	 *
	 * An interleave of 0 may not be used with a mirror setup.
	 */
	if (cs->sc_ileave == 0) {
		bn = 0;
		ii = cs->sc_itable;

		for (ix = 0; ix < cs->sc_ndisks; ix++) {
			/* Allocate space for ii_index. */
			ii->ii_index = g_malloc(sizeof(int), M_WAITOK);
			ii->ii_ndisk = 1;
			ii->ii_startblk = bn;
			ii->ii_startoff = 0;
			ii->ii_index[0] = ix;
			bn += cs->sc_cinfo[ix].ci_size;
			ii++;
		}
		ii->ii_ndisk = 0;
		return;
	}

	/*
	 * The following isn't fast or pretty; it doesn't have to be.
	 */
	size = 0;
	bn = lbn = 0;
	for (ii = cs->sc_itable; ; ii++) {
		/*
		 * Allocate space for ii_index.  We might allocate more then
		 * we use.
		 */
		ii->ii_index = g_malloc((sizeof(int) * cs->sc_ndisks),
		    M_WAITOK);

		/*
		 * Locate the smallest of the remaining components
		 */
		smallci = NULL;
		for (ci = cs->sc_cinfo; ci < &cs->sc_cinfo[cs->sc_ndisks]; 
		    ci++) {
			if (ci->ci_size > size &&
			    (smallci == NULL ||
			     ci->ci_size < smallci->ci_size)) {
				smallci = ci;
			}
		}

		/*
		 * Nobody left, all done
		 */
		if (smallci == NULL) {
			ii->ii_ndisk = 0;
			g_free(ii->ii_index);
			ii->ii_index = NULL;
			break;
		}

		/*
		 * Record starting logical block using an sc_ileave blocksize.
		 */
		ii->ii_startblk = bn / cs->sc_ileave;

		/*
		 * Record starting component block using an sc_ileave 
		 * blocksize.  This value is relative to the beginning of
		 * a component disk.
		 */
		ii->ii_startoff = lbn;

		/*
		 * Determine how many disks take part in this interleave
		 * and record their indices.
		 */
		ix = 0;
		for (ci = cs->sc_cinfo; 
		    ci < &cs->sc_cinfo[cs->sc_ndisks]; ci++) {
			if (ci->ci_size >= smallci->ci_size) {
				ii->ii_index[ix++] = ci - cs->sc_cinfo;
			}
		}
		ii->ii_ndisk = ix;
		bn += ix * (smallci->ci_size - size);
		lbn = smallci->ci_size / cs->sc_ileave;
		size = smallci->ci_size;
	}
}
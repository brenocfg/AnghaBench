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
typedef  int u_int ;
struct gctl_req {int dummy; } ;
struct ccdcinfo {int ci_size; TYPE_1__* ci_provider; } ;
struct ccd_s {int sc_size; int sc_flags; int sc_offset; int sc_ileave; int sc_ndisks; int sc_secsize; struct ccdcinfo* sc_cinfo; } ;
typedef  int off_t ;
typedef  int daddr_t ;
struct TYPE_2__ {int mediasize; int sectorsize; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CCDF_LINUX ; 
 int CCDF_MIRROR ; 
 int CCDF_NO_OFFSET ; 
 int CCDF_UNIFORM ; 
 int CCD_OFFSET ; 
 int DEV_BSIZE ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  ccdinterleave (struct ccd_s*) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 

__attribute__((used)) static int
ccdinit(struct gctl_req *req, struct ccd_s *cs)
{
	struct ccdcinfo *ci;
	daddr_t size;
	int ix;
	daddr_t minsize;
	int maxsecsize;
	off_t mediasize;
	u_int sectorsize;

	cs->sc_size = 0;

	maxsecsize = 0;
	minsize = 0;

	if (cs->sc_flags & CCDF_LINUX) {
		cs->sc_offset = 0;
		cs->sc_ileave *= 2;
		if (cs->sc_flags & CCDF_MIRROR && cs->sc_ndisks != 2)
			gctl_error(req, "Mirror mode for Linux raids is "
			                "only supported with 2 devices");
	} else {
		if (cs->sc_flags & CCDF_NO_OFFSET)
			cs->sc_offset = 0;
		else
			cs->sc_offset = CCD_OFFSET;

	}
	for (ix = 0; ix < cs->sc_ndisks; ix++) {
		ci = &cs->sc_cinfo[ix];

		mediasize = ci->ci_provider->mediasize;
		sectorsize = ci->ci_provider->sectorsize;
		if (sectorsize > maxsecsize)
			maxsecsize = sectorsize;
		size = mediasize / DEV_BSIZE - cs->sc_offset;

		/* Truncate to interleave boundary */

		if (cs->sc_ileave > 1)
			size -= size % cs->sc_ileave;

		if (size == 0) {
			gctl_error(req, "Component %s has effective size zero",
			    ci->ci_provider->name);
			return(ENODEV);
		}

		if (minsize == 0 || size < minsize)
			minsize = size;
		ci->ci_size = size;
		cs->sc_size += size;
	}

	/*
	 * Don't allow the interleave to be smaller than
	 * the biggest component sector.
	 */
	if ((cs->sc_ileave > 0) &&
	    (cs->sc_ileave < (maxsecsize / DEV_BSIZE))) {
		gctl_error(req, "Interleave to small for sector size");
		return(EINVAL);
	}

	/*
	 * If uniform interleave is desired set all sizes to that of
	 * the smallest component.  This will guarantee that a single
	 * interleave table is generated.
	 *
	 * Lost space must be taken into account when calculating the
	 * overall size.  Half the space is lost when CCDF_MIRROR is
	 * specified.
	 */
	if (cs->sc_flags & CCDF_UNIFORM) {
		for (ix = 0; ix < cs->sc_ndisks; ix++) {
			ci = &cs->sc_cinfo[ix];
			ci->ci_size = minsize;
		}
		cs->sc_size = cs->sc_ndisks * minsize;
	}

	if (cs->sc_flags & CCDF_MIRROR) {
		/*
		 * Check to see if an even number of components
		 * have been specified.  The interleave must also
		 * be non-zero in order for us to be able to 
		 * guarantee the topology.
		 */
		if (cs->sc_ndisks % 2) {
			gctl_error(req,
			      "Mirroring requires an even number of disks");
			return(EINVAL);
		}
		if (cs->sc_ileave == 0) {
			gctl_error(req,
			     "An interleave must be specified when mirroring");
			return(EINVAL);
		}
		cs->sc_size = (cs->sc_ndisks/2) * minsize;
	} 

	/*
	 * Construct the interleave table.
	 */
	ccdinterleave(cs);

	/*
	 * Create pseudo-geometry based on 1MB cylinders.  It's
	 * pretty close.
	 */
	cs->sc_secsize = maxsecsize;

	return (0);
}
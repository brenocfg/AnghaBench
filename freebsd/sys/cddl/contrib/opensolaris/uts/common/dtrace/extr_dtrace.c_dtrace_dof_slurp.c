#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  dtrace_vstate_t ;
typedef  int /*<<< orphan*/  dtrace_enabling_t ;
typedef  int /*<<< orphan*/  dtrace_ecbdesc_t ;
struct TYPE_9__ {int dofs_type; int dofs_flags; int dofs_align; int dofs_offset; scalar_t__ dofs_size; } ;
typedef  TYPE_1__ dof_sec_t ;
struct TYPE_10__ {scalar_t__ dofh_loadsz; scalar_t__* dofh_ident; int dofh_flags; scalar_t__ dofh_secsize; size_t dofh_secnum; scalar_t__ dofh_secoff; } ;
typedef  TYPE_2__ dof_hdr_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DIF_DIR_NREGS ; 
 scalar_t__ DIF_DTR_NREGS ; 
 scalar_t__ DIF_VERSION_2 ; 
 scalar_t__ DOF_ENCODE_NATIVE ; 
 int DOF_FL_VALID ; 
 size_t DOF_ID_DIFIREG ; 
 size_t DOF_ID_DIFTREG ; 
 size_t DOF_ID_DIFVERS ; 
 size_t DOF_ID_ENCODING ; 
 size_t DOF_ID_MAG0 ; 
 size_t DOF_ID_MODEL ; 
 size_t DOF_ID_PAD ; 
 size_t DOF_ID_SIZE ; 
 size_t DOF_ID_VERSION ; 
 int /*<<< orphan*/  DOF_MAG_STRING ; 
 int /*<<< orphan*/  DOF_MAG_STRLEN ; 
 scalar_t__ DOF_MODEL_ILP32 ; 
 scalar_t__ DOF_MODEL_LP64 ; 
 int DOF_SECF_LOAD ; 
 scalar_t__ DOF_SECT_ECBDESC ; 
#define  DOF_SECT_PRARGS 132 
#define  DOF_SECT_PROBES 131 
#define  DOF_SECT_PROFFS 130 
#define  DOF_SECT_PROVIDER 129 
 int DOF_SECT_STRTAB ; 
#define  DOF_SECT_URELHDR 128 
 scalar_t__ DOF_SEC_ISLOADABLE (int) ; 
 scalar_t__ DOF_VERSION_1 ; 
 scalar_t__ DOF_VERSION_2 ; 
 int /*<<< orphan*/  ISP2 (int) ; 
 int /*<<< orphan*/  IS_P2ALIGNED (scalar_t__,int) ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 scalar_t__ bcmp (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dtrace_dof_ecbdesc (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_dof_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dtrace_dof_relocate (TYPE_2__*,TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dtrace_enabling_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dtrace_enabling_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_enabling_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_lock ; 

__attribute__((used)) static int
dtrace_dof_slurp(dof_hdr_t *dof, dtrace_vstate_t *vstate, cred_t *cr,
    dtrace_enabling_t **enabp, uint64_t ubase, uint64_t udaddr, int noprobes)
{
	uint64_t len = dof->dofh_loadsz, seclen;
	uintptr_t daddr = (uintptr_t)dof;
	dtrace_ecbdesc_t *ep;
	dtrace_enabling_t *enab;
	uint_t i;

	ASSERT(MUTEX_HELD(&dtrace_lock));
	ASSERT(dof->dofh_loadsz >= sizeof (dof_hdr_t));

	/*
	 * Check the DOF header identification bytes.  In addition to checking
	 * valid settings, we also verify that unused bits/bytes are zeroed so
	 * we can use them later without fear of regressing existing binaries.
	 */
	if (bcmp(&dof->dofh_ident[DOF_ID_MAG0],
	    DOF_MAG_STRING, DOF_MAG_STRLEN) != 0) {
		dtrace_dof_error(dof, "DOF magic string mismatch");
		return (-1);
	}

	if (dof->dofh_ident[DOF_ID_MODEL] != DOF_MODEL_ILP32 &&
	    dof->dofh_ident[DOF_ID_MODEL] != DOF_MODEL_LP64) {
		dtrace_dof_error(dof, "DOF has invalid data model");
		return (-1);
	}

	if (dof->dofh_ident[DOF_ID_ENCODING] != DOF_ENCODE_NATIVE) {
		dtrace_dof_error(dof, "DOF encoding mismatch");
		return (-1);
	}

	if (dof->dofh_ident[DOF_ID_VERSION] != DOF_VERSION_1 &&
	    dof->dofh_ident[DOF_ID_VERSION] != DOF_VERSION_2) {
		dtrace_dof_error(dof, "DOF version mismatch");
		return (-1);
	}

	if (dof->dofh_ident[DOF_ID_DIFVERS] != DIF_VERSION_2) {
		dtrace_dof_error(dof, "DOF uses unsupported instruction set");
		return (-1);
	}

	if (dof->dofh_ident[DOF_ID_DIFIREG] > DIF_DIR_NREGS) {
		dtrace_dof_error(dof, "DOF uses too many integer registers");
		return (-1);
	}

	if (dof->dofh_ident[DOF_ID_DIFTREG] > DIF_DTR_NREGS) {
		dtrace_dof_error(dof, "DOF uses too many tuple registers");
		return (-1);
	}

	for (i = DOF_ID_PAD; i < DOF_ID_SIZE; i++) {
		if (dof->dofh_ident[i] != 0) {
			dtrace_dof_error(dof, "DOF has invalid ident byte set");
			return (-1);
		}
	}

	if (dof->dofh_flags & ~DOF_FL_VALID) {
		dtrace_dof_error(dof, "DOF has invalid flag bits set");
		return (-1);
	}

	if (dof->dofh_secsize == 0) {
		dtrace_dof_error(dof, "zero section header size");
		return (-1);
	}

	/*
	 * Check that the section headers don't exceed the amount of DOF
	 * data.  Note that we cast the section size and number of sections
	 * to uint64_t's to prevent possible overflow in the multiplication.
	 */
	seclen = (uint64_t)dof->dofh_secnum * (uint64_t)dof->dofh_secsize;

	if (dof->dofh_secoff > len || seclen > len ||
	    dof->dofh_secoff + seclen > len) {
		dtrace_dof_error(dof, "truncated section headers");
		return (-1);
	}

	if (!IS_P2ALIGNED(dof->dofh_secoff, sizeof (uint64_t))) {
		dtrace_dof_error(dof, "misaligned section headers");
		return (-1);
	}

	if (!IS_P2ALIGNED(dof->dofh_secsize, sizeof (uint64_t))) {
		dtrace_dof_error(dof, "misaligned section size");
		return (-1);
	}

	/*
	 * Take an initial pass through the section headers to be sure that
	 * the headers don't have stray offsets.  If the 'noprobes' flag is
	 * set, do not permit sections relating to providers, probes, or args.
	 */
	for (i = 0; i < dof->dofh_secnum; i++) {
		dof_sec_t *sec = (dof_sec_t *)(daddr +
		    (uintptr_t)dof->dofh_secoff + i * dof->dofh_secsize);

		if (noprobes) {
			switch (sec->dofs_type) {
			case DOF_SECT_PROVIDER:
			case DOF_SECT_PROBES:
			case DOF_SECT_PRARGS:
			case DOF_SECT_PROFFS:
				dtrace_dof_error(dof, "illegal sections "
				    "for enabling");
				return (-1);
			}
		}

		if (DOF_SEC_ISLOADABLE(sec->dofs_type) &&
		    !(sec->dofs_flags & DOF_SECF_LOAD)) {
			dtrace_dof_error(dof, "loadable section with load "
			    "flag unset");
			return (-1);
		}

		if (!(sec->dofs_flags & DOF_SECF_LOAD))
			continue; /* just ignore non-loadable sections */

		if (!ISP2(sec->dofs_align)) {
			dtrace_dof_error(dof, "bad section alignment");
			return (-1);
		}

		if (sec->dofs_offset & (sec->dofs_align - 1)) {
			dtrace_dof_error(dof, "misaligned section");
			return (-1);
		}

		if (sec->dofs_offset > len || sec->dofs_size > len ||
		    sec->dofs_offset + sec->dofs_size > len) {
			dtrace_dof_error(dof, "corrupt section header");
			return (-1);
		}

		if (sec->dofs_type == DOF_SECT_STRTAB && *((char *)daddr +
		    sec->dofs_offset + sec->dofs_size - 1) != '\0') {
			dtrace_dof_error(dof, "non-terminating string table");
			return (-1);
		}
	}

	/*
	 * Take a second pass through the sections and locate and perform any
	 * relocations that are present.  We do this after the first pass to
	 * be sure that all sections have had their headers validated.
	 */
	for (i = 0; i < dof->dofh_secnum; i++) {
		dof_sec_t *sec = (dof_sec_t *)(daddr +
		    (uintptr_t)dof->dofh_secoff + i * dof->dofh_secsize);

		if (!(sec->dofs_flags & DOF_SECF_LOAD))
			continue; /* skip sections that are not loadable */

		switch (sec->dofs_type) {
		case DOF_SECT_URELHDR:
			if (dtrace_dof_relocate(dof, sec, ubase, udaddr) != 0)
				return (-1);
			break;
		}
	}

	if ((enab = *enabp) == NULL)
		enab = *enabp = dtrace_enabling_create(vstate);

	for (i = 0; i < dof->dofh_secnum; i++) {
		dof_sec_t *sec = (dof_sec_t *)(daddr +
		    (uintptr_t)dof->dofh_secoff + i * dof->dofh_secsize);

		if (sec->dofs_type != DOF_SECT_ECBDESC)
			continue;

		if ((ep = dtrace_dof_ecbdesc(dof, sec, vstate, cr)) == NULL) {
			dtrace_enabling_destroy(enab);
			*enabp = NULL;
			return (-1);
		}

		dtrace_enabling_add(enab, ep);
	}

	return (0);
}
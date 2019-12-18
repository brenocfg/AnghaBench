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
typedef  size_t u_long ;
struct partition {size_t p_size; size_t p_offset; int p_fstype; size_t p_fsize; size_t p_frag; size_t p_cpg; } ;
struct disklabel {struct partition* d_partitions; } ;

/* Variables and functions */
 size_t FSMAXTYPES ; 
#define  FS_BSDFFS 130 
#define  FS_BSDLFS 129 
#define  FS_UNUSED 128 
 int /*<<< orphan*/  NXTNUM (size_t) ; 
 int /*<<< orphan*/  NXTWORD (char,size_t) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 char const** fstypenames ; 
 scalar_t__ isdigit (char) ; 
 char* part_offset_type ; 
 char* part_size_type ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 size_t strtoul (char*,char**,int) ; 
 char* word (char*) ; 

__attribute__((used)) static int
getasciipartspec(char *tp, struct disklabel *lp, int part, int lineno)
{
	struct partition *pp;
	char *cp, *endp;
	const char **cpp;
	u_long v;

	pp = &lp->d_partitions[part];
	cp = NULL;

	v = 0;
	NXTWORD(part_size_type[part],v);
	if (v == 0 && part_size_type[part] != '*') {
		fprintf(stderr,
		    "line %d: %s: bad partition size\n", lineno, cp);
		return (1);
	}
	pp->p_size = v;

	v = 0;
	NXTWORD(part_offset_type[part],v);
	if (v == 0 && part_offset_type[part] != '*' &&
	    part_offset_type[part] != '\0') {
		fprintf(stderr,
		    "line %d: %s: bad partition offset\n", lineno, cp);
		return (1);
	}
	pp->p_offset = v;
	if (tp == NULL) {
		fprintf(stderr, "line %d: missing file system type\n", lineno);
		return (1);
	}
	cp = tp, tp = word(cp);
	for (cpp = fstypenames; cpp < &fstypenames[FSMAXTYPES]; cpp++)
		if (*cpp && !strcmp(*cpp, cp))
			break;
	if (*cpp != NULL) {
		pp->p_fstype = cpp - fstypenames;
	} else {
		if (isdigit(*cp)) {
			errno = 0;
			v = strtoul(cp, &endp, 10);
			if (errno != 0 || *endp != '\0')
				v = FSMAXTYPES;
		} else
			v = FSMAXTYPES;
		if (v >= FSMAXTYPES) {
			fprintf(stderr,
			    "line %d: Warning, unknown file system type %s\n",
			    lineno, cp);
			v = FS_UNUSED;
		}
		pp->p_fstype = v;
	}

	switch (pp->p_fstype) {
	case FS_UNUSED:
	case FS_BSDFFS:
	case FS_BSDLFS:
		/* accept defaults for fsize/frag/cpg */
		if (tp) {
			NXTNUM(pp->p_fsize);
			if (pp->p_fsize == 0)
				break;
			NXTNUM(v);
			pp->p_frag = v / pp->p_fsize;
			if (tp != NULL)
				NXTNUM(pp->p_cpg);
		}
		/* else default to 0's */
		break;
	default:
		break;
	}
	return (0);
}
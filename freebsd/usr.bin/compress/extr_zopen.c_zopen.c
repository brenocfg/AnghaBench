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
struct s_zstate {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BITS ; 
 int /*<<< orphan*/  BLOCK_MASK ; 
 int /*<<< orphan*/  CHECK_GAP ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  HSIZE ; 
 int /*<<< orphan*/  S_START ; 
 int /*<<< orphan*/  block_compress ; 
 struct s_zstate* calloc (int,int) ; 
 int /*<<< orphan*/  checkpoint ; 
 scalar_t__ clear_flg ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/ * fp ; 
 int /*<<< orphan*/  free (struct s_zstate*) ; 
 scalar_t__ free_ent ; 
 int /*<<< orphan*/ * funopen (struct s_zstate*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsize ; 
 int in_count ; 
 long maxbits ; 
 long maxmaxcode ; 
 scalar_t__ out_count ; 
 scalar_t__ ratio ; 
 scalar_t__ roffset ; 
 scalar_t__ size ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  zclose ; 
 char zmode ; 
 int /*<<< orphan*/ * zread ; 
 int /*<<< orphan*/ * zwrite ; 

FILE *
zopen(const char *fname, const char *mode, int bits)
{
	struct s_zstate *zs;

	if ((mode[0] != 'r' && mode[0] != 'w') || mode[1] != '\0' ||
	    bits < 0 || bits > BITS) {
		errno = EINVAL;
		return (NULL);
	}

	if ((zs = calloc(1, sizeof(struct s_zstate))) == NULL)
		return (NULL);

	maxbits = bits ? bits : BITS;	/* User settable max # bits/code. */
	maxmaxcode = 1L << maxbits;	/* Should NEVER generate this code. */
	hsize = HSIZE;			/* For dynamic table sizing. */
	free_ent = 0;			/* First unused entry. */
	block_compress = BLOCK_MASK;
	clear_flg = 0;
	ratio = 0;
	checkpoint = CHECK_GAP;
	in_count = 1;			/* Length of input. */
	out_count = 0;			/* # of codes output (for debugging). */
	state = S_START;
	roffset = 0;
	size = 0;

	/*
	 * Layering compress on top of stdio in order to provide buffering,
	 * and ensure that reads and write work with the data specified.
	 */
	if ((fp = fopen(fname, mode)) == NULL) {
		free(zs);
		return (NULL);
	}
	switch (*mode) {
	case 'r':
		zmode = 'r';
		return (funopen(zs, zread, NULL, NULL, zclose));
	case 'w':
		zmode = 'w';
		return (funopen(zs, NULL, zwrite, NULL, zclose));
	}
	/* NOTREACHED */
	return (NULL);
}
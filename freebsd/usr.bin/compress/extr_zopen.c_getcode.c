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
typedef  int code_int ;
typedef  int char_type ;

/* Variables and functions */
 int INIT_BITS ; 
 scalar_t__ MAXCODE (int) ; 
 scalar_t__ clear_flg ; 
 int /*<<< orphan*/  fp ; 
 int fread (int*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ free_ent ; 
 int* gbuf ; 
 int maxbits ; 
 scalar_t__ maxcode ; 
 scalar_t__ maxmaxcode ; 
 int n_bits ; 
 int* rmask ; 
 int roffset ; 
 int size ; 

__attribute__((used)) static code_int
getcode(struct s_zstate *zs)
{
	code_int gcode;
	int r_off, bits;
	char_type *bp;

	bp = gbuf;
	if (clear_flg > 0 || roffset >= size || free_ent > maxcode) {
		/*
		 * If the next entry will be too big for the current gcode
		 * size, then we must increase the size.  This implies reading
		 * a new buffer full, too.
		 */
		if (free_ent > maxcode) {
			n_bits++;
			if (n_bits == maxbits)	/* Won't get any bigger now. */
				maxcode = maxmaxcode;
			else
				maxcode = MAXCODE(n_bits);
		}
		if (clear_flg > 0) {
			maxcode = MAXCODE(n_bits = INIT_BITS);
			clear_flg = 0;
		}
		size = fread(gbuf, 1, n_bits, fp);
		if (size <= 0)			/* End of file. */
			return (-1);
		roffset = 0;
		/* Round size down to integral number of codes. */
		size = (size << 3) - (n_bits - 1);
	}
	r_off = roffset;
	bits = n_bits;

	/* Get to the first byte. */
	bp += (r_off >> 3);
	r_off &= 7;

	/* Get first part (low order bits). */
	gcode = (*bp++ >> r_off);
	bits -= (8 - r_off);
	r_off = 8 - r_off;	/* Now, roffset into gcode word. */

	/* Get any 8 bit parts in the middle (<=1 for up to 16 bits). */
	if (bits >= 8) {
		gcode |= *bp++ << r_off;
		r_off += 8;
		bits -= 8;
	}

	/* High order bits. */
	gcode |= (*bp & rmask[bits]) << r_off;
	roffset += n_bits;

	return (gcode);
}
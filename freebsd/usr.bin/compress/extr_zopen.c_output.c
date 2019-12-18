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
typedef  int u_int ;
struct s_zstate {int dummy; } ;
typedef  int code_int ;
typedef  int char_type ;

/* Variables and functions */
 int INIT_BITS ; 
 scalar_t__ MAXCODE (int) ; 
 int* buf ; 
 int bytes_out ; 
 scalar_t__ clear_flg ; 
 int /*<<< orphan*/  fp ; 
 scalar_t__ free_ent ; 
 int fwrite (int*,int,int,int /*<<< orphan*/ ) ; 
 int* lmask ; 
 int maxbits ; 
 scalar_t__ maxcode ; 
 scalar_t__ maxmaxcode ; 
 int n_bits ; 
 int offset ; 
 int* rmask ; 

__attribute__((used)) static int
output(struct s_zstate *zs, code_int ocode)
{
	int r_off;
	u_int bits;
	char_type *bp;

	r_off = offset;
	bits = n_bits;
	bp = buf;
	if (ocode >= 0) {
		/* Get to the first byte. */
		bp += (r_off >> 3);
		r_off &= 7;
		/*
		 * Since ocode is always >= 8 bits, only need to mask the first
		 * hunk on the left.
		 */
		*bp = (*bp & rmask[r_off]) | ((ocode << r_off) & lmask[r_off]);
		bp++;
		bits -= (8 - r_off);
		ocode >>= 8 - r_off;
		/* Get any 8 bit parts in the middle (<=1 for up to 16 bits). */
		if (bits >= 8) {
			*bp++ = ocode;
			ocode >>= 8;
			bits -= 8;
		}
		/* Last bits. */
		if (bits)
			*bp = ocode;
		offset += n_bits;
		if (offset == (n_bits << 3)) {
			bp = buf;
			bits = n_bits;
			bytes_out += bits;
			if (fwrite(bp, sizeof(char), bits, fp) != bits)
				return (-1);
			bp += bits;
			bits = 0;
			offset = 0;
		}
		/*
		 * If the next entry is going to be too big for the ocode size,
		 * then increase it, if possible.
		 */
		if (free_ent > maxcode || (clear_flg > 0)) {
		       /*
			* Write the whole buffer, because the input side won't
			* discover the size increase until after it has read it.
			*/
			if (offset > 0) {
				if (fwrite(buf, 1, n_bits, fp) != n_bits)
					return (-1);
				bytes_out += n_bits;
			}
			offset = 0;

			if (clear_flg) {
				maxcode = MAXCODE(n_bits = INIT_BITS);
				clear_flg = 0;
			} else {
				n_bits++;
				if (n_bits == maxbits)
					maxcode = maxmaxcode;
				else
					maxcode = MAXCODE(n_bits);
			}
		}
	} else {
		/* At EOF, write the rest of the buffer. */
		if (offset > 0) {
			offset = (offset + 7) / 8;
			if (fwrite(buf, 1, offset, fp) != offset)
				return (-1);
			bytes_out += offset;
		}
		offset = 0;
	}
	return (0);
}
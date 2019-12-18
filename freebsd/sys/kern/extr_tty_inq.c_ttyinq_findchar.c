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
struct ttyinq_block {char* tib_data; } ;
struct ttyinq {unsigned int ti_begin; size_t ti_linestart; struct ttyinq_block* ti_firstblock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GETBIT (struct ttyinq_block*,unsigned int) ; 
 unsigned int MIN (unsigned int,size_t) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 unsigned int TTYINQ_DATASIZE ; 
 scalar_t__ strchr (char const*,char) ; 

size_t
ttyinq_findchar(struct ttyinq *ti, const char *breakc, size_t maxlen,
    char *lastc)
{
	struct ttyinq_block *tib = ti->ti_firstblock;
	unsigned int boff = ti->ti_begin;
	unsigned int bend = MIN(MIN(TTYINQ_DATASIZE, ti->ti_linestart),
	    ti->ti_begin + maxlen);

	MPASS(maxlen > 0);

	if (tib == NULL)
		return (0);

	while (boff < bend) {
		if (strchr(breakc, tib->tib_data[boff]) && !GETBIT(tib, boff)) {
			*lastc = tib->tib_data[boff];
			return (boff - ti->ti_begin + 1);
		}
		boff++;
	}

	/* Not found - just process the entire block. */
	return (bend - ti->ti_begin);
}
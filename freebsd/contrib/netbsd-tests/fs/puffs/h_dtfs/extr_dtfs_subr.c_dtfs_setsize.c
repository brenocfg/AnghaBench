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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ va_size; int va_bytes; } ;
struct puffs_node {TYPE_1__ pn_va; } ;
struct dtfs_mount {int /*<<< orphan*/  dtm_fsizes; } ;
struct dtfs_file {int df_numblocks; scalar_t__ df_datalen; int /*<<< orphan*/ * df_blocks; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int BLOCKNUM (scalar_t__,int) ; 
 int DTFS_BLOCKSHIFT ; 
 int /*<<< orphan*/  DTFS_BLOCKSIZE ; 
 struct dtfs_file* DTFS_PTOF (struct puffs_node*) ; 
 scalar_t__ ROUNDUP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * erealloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dtfs_mount* puffs_pn_getmntspecific (struct puffs_node*) ; 

void
dtfs_setsize(struct puffs_node *pn, off_t newsize)
{
	struct dtfs_file *df = DTFS_PTOF(pn);
	struct dtfs_mount *dtm;
	size_t newblocks;
	int needalloc, shrinks;
	int i;

	needalloc = newsize > ROUNDUP(df->df_datalen, DTFS_BLOCKSIZE);
	shrinks = newsize < pn->pn_va.va_size;

	if (needalloc || shrinks) {
		newblocks = BLOCKNUM(newsize, DTFS_BLOCKSHIFT) + 1;

		if (shrinks)
			for (i = newblocks; i < df->df_numblocks; i++)
				free(df->df_blocks[i]);

		df->df_blocks = erealloc(df->df_blocks,
		    newblocks * sizeof(uint8_t *));
		/*
		 * if extended, set storage to zero
		 * to match correct behaviour
		 */ 
		if (!shrinks) {
			for (i = df->df_numblocks; i < newblocks; i++) {
				df->df_blocks[i] = emalloc(DTFS_BLOCKSIZE);
				memset(df->df_blocks[i], 0, DTFS_BLOCKSIZE);
			}
		}

		df->df_datalen = newsize;
		df->df_numblocks = newblocks;
	}

	dtm = puffs_pn_getmntspecific(pn);
	if (!shrinks) {
		dtm->dtm_fsizes += newsize - pn->pn_va.va_size;
	} else {
		dtm->dtm_fsizes -= pn->pn_va.va_size - newsize;
	}

	pn->pn_va.va_size = newsize;
	pn->pn_va.va_bytes = BLOCKNUM(newsize,DTFS_BLOCKSHIFT)>>DTFS_BLOCKSHIFT;
}
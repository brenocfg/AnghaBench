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
struct puffs_usermount {int dummy; } ;
struct TYPE_2__ {scalar_t__ va_type; scalar_t__ va_size; } ;
struct puffs_node {TYPE_1__ pn_va; } ;
struct puffs_cred {int dummy; } ;
struct dtfs_file {int /*<<< orphan*/ ** df_blocks; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKLEFT (scalar_t__,int /*<<< orphan*/ ) ; 
 int BLOCKNUM (scalar_t__,int /*<<< orphan*/ ) ; 
 int BLOCKOFF (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTFS_BLOCKSHIFT ; 
 int /*<<< orphan*/  DTFS_BLOCKSIZE ; 
 struct dtfs_file* DTFS_CTOF (void*) ; 
 int EISDIR ; 
 size_t MIN (size_t,int /*<<< orphan*/ ) ; 
 int PUFFS_IO_APPEND ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  dtfs_setsize (struct puffs_node*,scalar_t__) ; 
 int /*<<< orphan*/  dtfs_updatetimes (struct puffs_node*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

int
dtfs_node_write(struct puffs_usermount *pu, void *opc, uint8_t *buf,
	off_t offset, size_t *resid, const struct puffs_cred *pcr, int ioflag)
{
	struct puffs_node *pn = opc;
	struct dtfs_file *df = DTFS_CTOF(opc);
	uint8_t *src, *dest;
	size_t copylen;

	if (pn->pn_va.va_type != VREG)
		return EISDIR;

	if (ioflag & PUFFS_IO_APPEND)
		offset = pn->pn_va.va_size;

	if (*resid + offset > pn->pn_va.va_size)
		dtfs_setsize(pn, *resid + offset);

	src = buf;
	while (*resid > 0) {
		int i;
		copylen = MIN(*resid, BLOCKLEFT(offset, DTFS_BLOCKSIZE));
		i = BLOCKNUM(offset, DTFS_BLOCKSHIFT);
		dest = df->df_blocks[i]
		    + BLOCKOFF(offset, DTFS_BLOCKSIZE);
		memcpy(dest, src, copylen);
		offset += copylen;
		dest += copylen;
		*resid -= copylen;
	}

	dtfs_updatetimes(pn, 0, 1, 1);

	return 0;
}
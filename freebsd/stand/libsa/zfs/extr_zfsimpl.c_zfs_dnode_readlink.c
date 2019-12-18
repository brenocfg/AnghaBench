#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  znode_phys_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  sa_hdr_phys_t ;
struct TYPE_6__ {scalar_t__ dn_bonustype; size_t dn_bonuslen; int dn_flags; char* dn_bonus; } ;
typedef  TYPE_1__ dnode_phys_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 size_t BP_GET_LSIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ DMU_OT_SA ; 
 int DNODE_FLAG_SPILL_BLKPTR ; 
 scalar_t__ DN_BONUS (TYPE_1__*) ; 
 int /*<<< orphan*/ * DN_SPILL_BLKPTR (TYPE_1__*) ; 
 int EIO ; 
 int SA_HDR_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ SA_SYMLINK_OFFSET ; 
 int dnode_read (int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 void* zfs_alloc (size_t) ; 
 int /*<<< orphan*/  zfs_free (void*,size_t) ; 
 int zio_read (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int
zfs_dnode_readlink(const spa_t *spa, dnode_phys_t *dn, char *path, size_t psize)
{
	int rc = 0;

	if (dn->dn_bonustype == DMU_OT_SA) {
		sa_hdr_phys_t *sahdrp = NULL;
		size_t size = 0;
		void *buf = NULL;
		int hdrsize;
		char *p;

		if (dn->dn_bonuslen != 0)
			sahdrp = (sa_hdr_phys_t *)DN_BONUS(dn);
		else {
			blkptr_t *bp;

			if ((dn->dn_flags & DNODE_FLAG_SPILL_BLKPTR) == 0)
				return (EIO);
			bp = DN_SPILL_BLKPTR(dn);

			size = BP_GET_LSIZE(bp);
			buf = zfs_alloc(size);
			rc = zio_read(spa, bp, buf);
			if (rc != 0) {
				zfs_free(buf, size);
				return (rc);
			}
			sahdrp = buf;
		}
		hdrsize = SA_HDR_SIZE(sahdrp);
		p = (char *)((uintptr_t)sahdrp + hdrsize + SA_SYMLINK_OFFSET);
		memcpy(path, p, psize);
		if (buf != NULL)
			zfs_free(buf, size);
		return (0);
	}
	/*
	 * Second test is purely to silence bogus compiler
	 * warning about accessing past the end of dn_bonus.
	 */
	if (psize + sizeof(znode_phys_t) <= dn->dn_bonuslen &&
	    sizeof(znode_phys_t) <= sizeof(dn->dn_bonus)) {
		memcpy(path, &dn->dn_bonus[sizeof(znode_phys_t)], psize);
	} else {
		rc = dnode_read(spa, dn, 0, path, psize);
	}
	return (rc);
}
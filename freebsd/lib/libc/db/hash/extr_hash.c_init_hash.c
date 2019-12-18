#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_blksize; } ;
struct TYPE_8__ {int bsize; int nelem; scalar_t__ lorder; scalar_t__ hash; scalar_t__ ffactor; } ;
struct TYPE_7__ {scalar_t__ LORDER; int BSIZE; int BSHIFT; scalar_t__ hash; scalar_t__ FFACTOR; int /*<<< orphan*/  BITMAPS; int /*<<< orphan*/  SPARES; int /*<<< orphan*/  DSIZE; int /*<<< orphan*/  SSHIFT; int /*<<< orphan*/  SGSIZE; scalar_t__ NKEYS; } ;
typedef  TYPE_1__ HTAB ;
typedef  TYPE_2__ HASHINFO ;

/* Variables and functions */
 scalar_t__ BIG_ENDIAN ; 
 scalar_t__ BYTE_ORDER ; 
 int DEF_BUCKET_SHIFT ; 
 int DEF_BUCKET_SIZE ; 
 int /*<<< orphan*/  DEF_DIRSIZE ; 
 scalar_t__ DEF_FFACTOR ; 
 int /*<<< orphan*/  DEF_SEGSIZE ; 
 int /*<<< orphan*/  DEF_SEGSIZE_SHIFT ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ LITTLE_ENDIAN ; 
 int MAX_BSIZE ; 
 scalar_t__ __default_hash ; 
 void* __log2 (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ init_htab (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static HTAB *
init_hash(HTAB *hashp, const char *file, const HASHINFO *info)
{
	struct stat statbuf;
	int nelem;

	nelem = 1;
	hashp->NKEYS = 0;
	hashp->LORDER = BYTE_ORDER;
	hashp->BSIZE = DEF_BUCKET_SIZE;
	hashp->BSHIFT = DEF_BUCKET_SHIFT;
	hashp->SGSIZE = DEF_SEGSIZE;
	hashp->SSHIFT = DEF_SEGSIZE_SHIFT;
	hashp->DSIZE = DEF_DIRSIZE;
	hashp->FFACTOR = DEF_FFACTOR;
	hashp->hash = __default_hash;
	memset(hashp->SPARES, 0, sizeof(hashp->SPARES));
	memset(hashp->BITMAPS, 0, sizeof (hashp->BITMAPS));

	/* Fix bucket size to be optimal for file system */
	if (file != NULL) {
		if (stat(file, &statbuf))
			return (NULL);
		hashp->BSIZE = statbuf.st_blksize;
		if (hashp->BSIZE > MAX_BSIZE)
			hashp->BSIZE = MAX_BSIZE;
		hashp->BSHIFT = __log2(hashp->BSIZE);
	}

	if (info) {
		if (info->bsize) {
			/* Round pagesize up to power of 2 */
			hashp->BSHIFT = __log2(info->bsize);
			hashp->BSIZE = 1 << hashp->BSHIFT;
			if (hashp->BSIZE > MAX_BSIZE) {
				errno = EINVAL;
				return (NULL);
			}
		}
		if (info->ffactor)
			hashp->FFACTOR = info->ffactor;
		if (info->hash)
			hashp->hash = info->hash;
		if (info->nelem)
			nelem = info->nelem;
		if (info->lorder) {
			if (info->lorder != BIG_ENDIAN &&
			    info->lorder != LITTLE_ENDIAN) {
				errno = EINVAL;
				return (NULL);
			}
			hashp->LORDER = info->lorder;
		}
	}
	/* init_htab should destroy the table and set errno if it fails */
	if (init_htab(hashp, nelem))
		return (NULL);
	else
		return (hashp);
}
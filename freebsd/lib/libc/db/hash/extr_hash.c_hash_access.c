#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_26__ {int /*<<< orphan*/  flags; scalar_t__ page; } ;
struct TYPE_25__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_24__ {int BSIZE; } ;
typedef  TYPE_1__ HTAB ;
typedef  TYPE_2__ DBT ;
typedef  TYPE_3__ BUFHEAD ;
typedef  int ACTION ;

/* Variables and functions */
 int ABNORMAL ; 
 int /*<<< orphan*/  BUF_PIN ; 
 int ERROR ; 
#define  HASH_DELETE 131 
#define  HASH_GET 130 
#define  HASH_PUT 129 
#define  HASH_PUTNEW 128 
 int OVFLPAGE ; 
 int REAL_KEY ; 
 int SUCCESS ; 
 int /*<<< orphan*/  __addel (TYPE_1__*,TYPE_3__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  __big_return (TYPE_1__*,TYPE_3__*,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int __call_hash (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  __delpair (TYPE_1__*,TYPE_3__*,int) ; 
 int __find_bigpair (TYPE_1__*,TYPE_3__*,int,char*,int) ; 
 int __find_last_page (TYPE_1__*,TYPE_3__**) ; 
 TYPE_3__* __get_buf (TYPE_1__*,int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  hash_accesses ; 
 int /*<<< orphan*/  hash_collisions ; 
 scalar_t__ memcmp (char*,scalar_t__,int) ; 

__attribute__((used)) static int
hash_access(HTAB *hashp, ACTION action, DBT *key, DBT *val)
{
	BUFHEAD *rbufp;
	BUFHEAD *bufp, *save_bufp;
	u_int16_t *bp;
	int n, ndx, off, size;
	char *kp;
	u_int16_t pageno;

#ifdef HASH_STATISTICS
	hash_accesses++;
#endif

	off = hashp->BSIZE;
	size = key->size;
	kp = (char *)key->data;
	rbufp = __get_buf(hashp, __call_hash(hashp, kp, size), NULL, 0);
	if (!rbufp)
		return (ERROR);
	save_bufp = rbufp;

	/* Pin the bucket chain */
	rbufp->flags |= BUF_PIN;
	for (bp = (u_int16_t *)rbufp->page, n = *bp++, ndx = 1; ndx < n;)
		if (bp[1] >= REAL_KEY) {
			/* Real key/data pair */
			if (size == off - *bp &&
			    memcmp(kp, rbufp->page + *bp, size) == 0)
				goto found;
			off = bp[1];
#ifdef HASH_STATISTICS
			hash_collisions++;
#endif
			bp += 2;
			ndx += 2;
		} else if (bp[1] == OVFLPAGE) {
			rbufp = __get_buf(hashp, *bp, rbufp, 0);
			if (!rbufp) {
				save_bufp->flags &= ~BUF_PIN;
				return (ERROR);
			}
			/* FOR LOOP INIT */
			bp = (u_int16_t *)rbufp->page;
			n = *bp++;
			ndx = 1;
			off = hashp->BSIZE;
		} else if (bp[1] < REAL_KEY) {
			if ((ndx =
			    __find_bigpair(hashp, rbufp, ndx, kp, size)) > 0)
				goto found;
			if (ndx == -2) {
				bufp = rbufp;
				if (!(pageno =
				    __find_last_page(hashp, &bufp))) {
					ndx = 0;
					rbufp = bufp;
					break;	/* FOR */
				}
				rbufp = __get_buf(hashp, pageno, bufp, 0);
				if (!rbufp) {
					save_bufp->flags &= ~BUF_PIN;
					return (ERROR);
				}
				/* FOR LOOP INIT */
				bp = (u_int16_t *)rbufp->page;
				n = *bp++;
				ndx = 1;
				off = hashp->BSIZE;
			} else {
				save_bufp->flags &= ~BUF_PIN;
				return (ERROR);
			}
		}

	/* Not found */
	switch (action) {
	case HASH_PUT:
	case HASH_PUTNEW:
		if (__addel(hashp, rbufp, key, val)) {
			save_bufp->flags &= ~BUF_PIN;
			return (ERROR);
		} else {
			save_bufp->flags &= ~BUF_PIN;
			return (SUCCESS);
		}
	case HASH_GET:
	case HASH_DELETE:
	default:
		save_bufp->flags &= ~BUF_PIN;
		return (ABNORMAL);
	}

found:
	switch (action) {
	case HASH_PUTNEW:
		save_bufp->flags &= ~BUF_PIN;
		return (ABNORMAL);
	case HASH_GET:
		bp = (u_int16_t *)rbufp->page;
		if (bp[ndx + 1] < REAL_KEY) {
			if (__big_return(hashp, rbufp, ndx, val, 0))
				return (ERROR);
		} else {
			val->data = (u_char *)rbufp->page + (int)bp[ndx + 1];
			val->size = bp[ndx] - bp[ndx + 1];
		}
		break;
	case HASH_PUT:
		if ((__delpair(hashp, rbufp, ndx)) ||
		    (__addel(hashp, rbufp, key, val))) {
			save_bufp->flags &= ~BUF_PIN;
			return (ERROR);
		}
		break;
	case HASH_DELETE:
		if (__delpair(hashp, rbufp, ndx))
			return (ERROR);
		break;
	default:
		abort();
	}
	save_bufp->flags &= ~BUF_PIN;
	return (SUCCESS);
}
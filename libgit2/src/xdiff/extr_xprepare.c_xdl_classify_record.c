#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* ptr; unsigned long ha; struct TYPE_9__* next; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ xrecord_t ;
struct TYPE_10__ {unsigned int hbits; int count; int alloc; TYPE_3__** rchash; TYPE_3__** rcrecs; int /*<<< orphan*/  ncha; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ xdlclassifier_t ;
struct TYPE_11__ {unsigned long ha; char const* line; size_t idx; scalar_t__ len2; scalar_t__ len1; struct TYPE_11__* next; int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ xdlclass_t ;

/* Variables and functions */
 scalar_t__ XDL_HASHLONG (unsigned long,unsigned int) ; 
 TYPE_3__* xdl_cha_alloc (int /*<<< orphan*/ *) ; 
 scalar_t__ xdl_realloc (TYPE_3__**,int) ; 
 scalar_t__ xdl_recmatch (char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xdl_classify_record(unsigned int pass, xdlclassifier_t *cf, xrecord_t **rhash,
			       unsigned int hbits, xrecord_t *rec) {
	long hi;
	char const *line;
	xdlclass_t *rcrec;
	xdlclass_t **rcrecs;

	line = rec->ptr;
	hi = (long) XDL_HASHLONG(rec->ha, cf->hbits);
	for (rcrec = cf->rchash[hi]; rcrec; rcrec = rcrec->next)
		if (rcrec->ha == rec->ha &&
				xdl_recmatch(rcrec->line, rcrec->size,
					rec->ptr, rec->size, cf->flags))
			break;

	if (!rcrec) {
		if (!(rcrec = xdl_cha_alloc(&cf->ncha))) {

			return -1;
		}
		rcrec->idx = cf->count++;
		if (cf->count > cf->alloc) {
			cf->alloc *= 2;
			if (!(rcrecs = (xdlclass_t **) xdl_realloc(cf->rcrecs, cf->alloc * sizeof(xdlclass_t *)))) {

				return -1;
			}
			cf->rcrecs = rcrecs;
		}
		cf->rcrecs[rcrec->idx] = rcrec;
		rcrec->line = line;
		rcrec->size = rec->size;
		rcrec->ha = rec->ha;
		rcrec->len1 = rcrec->len2 = 0;
		rcrec->next = cf->rchash[hi];
		cf->rchash[hi] = rcrec;
	}

	(pass == 1) ? rcrec->len1++ : rcrec->len2++;

	rec->ha = (unsigned long) rcrec->idx;

	hi = (long) XDL_HASHLONG(rec->ha, hbits);
	rec->next = rhash[hi];
	rhash[hi] = rec;

	return 0;
}
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
struct shash_desc {int dummy; } ;
struct scatterlist {unsigned int offset; int /*<<< orphan*/  length; } ;
struct ahash_request {unsigned int nbytes; int /*<<< orphan*/  result; struct scatterlist* src; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int crypto_shash_digest (struct shash_desc*,void*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_shash_init (struct shash_desc*) ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int shash_ahash_finup (struct ahash_request*,struct shash_desc*) ; 

int shash_ahash_digest(struct ahash_request *req, struct shash_desc *desc)
{
	unsigned int nbytes = req->nbytes;
	struct scatterlist *sg;
	unsigned int offset;
	int err;

	if (nbytes &&
	    (sg = req->src, offset = sg->offset,
	     nbytes <= min(sg->length, ((unsigned int)(PAGE_SIZE)) - offset))) {
		void *data;

		data = kmap_atomic(sg_page(sg));
		err = crypto_shash_digest(desc, data + offset, nbytes,
					  req->result);
		kunmap_atomic(data);
	} else
		err = crypto_shash_init(desc) ?:
		      shash_ahash_finup(req, desc);

	return err;
}
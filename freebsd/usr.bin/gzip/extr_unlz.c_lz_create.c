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
struct lz_decoder {int dict_size; int wrapped; int /*<<< orphan*/ * fin; int /*<<< orphan*/  rdec; int /*<<< orphan*/ * obuf; int /*<<< orphan*/  crc; scalar_t__ spos; scalar_t__ ppos; scalar_t__ pos; int /*<<< orphan*/ * fout; } ;

/* Variables and functions */
 int /*<<< orphan*/  dup (int) ; 
 void* fdopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lz_destroy (struct lz_decoder*) ; 
 int lz_rd_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (struct lz_decoder*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lz_create(struct lz_decoder *lz, int fin, int fdout, int dict_size)
{
	memset(lz, 0, sizeof(*lz));

	lz->fin = fdopen(dup(fin), "r");
	if (lz->fin == NULL)
		goto out;

	lz->fout = fdopen(dup(fdout), "w");
	if (lz->fout == NULL)
		goto out;

	lz->pos = lz->ppos = lz->spos = 0;
	lz->crc = ~0;
	lz->dict_size = dict_size;
	lz->wrapped = false;

	lz->obuf = malloc(dict_size);
	if (lz->obuf == NULL)
		goto out;

	if (lz_rd_create(&lz->rdec, lz->fin) == -1)
		goto out;
	return 0;
out:
	lz_destroy(lz);
	return -1;
}
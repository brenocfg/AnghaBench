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
struct fifolog_reader {int olen; int /*<<< orphan*/  magic; TYPE_1__* ff; int /*<<< orphan*/ * obuf; } ;
struct TYPE_2__ {int recsize; int /*<<< orphan*/  zs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIFOLOG_READER_MAGIC ; 
 int Z_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 char* fifolog_int_open (TYPE_1__**,char const*,int /*<<< orphan*/ ) ; 
 int inflateInit (int /*<<< orphan*/ ) ; 

struct fifolog_reader *
fifolog_reader_open(const char *fname)
{
	const char *retval;
	struct fifolog_reader *fr;
	int i;

	fr = calloc(1, sizeof(*fr));
	if (fr == NULL)
		err(1, "Cannot malloc");

	retval = fifolog_int_open(&fr->ff, fname, 0);
	if (retval != NULL)
		err(1, "%s", retval);

	fr->obuf = calloc(16, fr->ff->recsize);
	if (fr->obuf == NULL)
		err(1, "Cannot malloc");
	fr->olen = fr->ff->recsize * 16;

	i = inflateInit(fr->ff->zs);
	assert(i == Z_OK);

	fr->magic = FIFOLOG_READER_MAGIC;
	return (fr);
}
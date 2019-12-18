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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nseq ; 
 int seq_addunit () ; 
 int seq_delunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seqinfo_mtx ; 

int
seq_modevent(module_t mod, int type, void *data)
{
	int retval, r;

	retval = 0;

	switch (type) {
	case MOD_LOAD:
		mtx_init(&seqinfo_mtx, "seqmod", NULL, 0);
		retval = seq_addunit();
		break;

	case MOD_UNLOAD:
		while (nseq) {
			r = seq_delunit(nseq - 1);
			if (r) {
				retval = r;
				break;
			}
		}
		if (nseq == 0) {
			retval = 0;
			mtx_destroy(&seqinfo_mtx);
		}
		break;

	default:
		break;
	}

	return retval;
}
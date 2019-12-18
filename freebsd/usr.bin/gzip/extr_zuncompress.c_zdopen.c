#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ zs_size; scalar_t__ zs_roffset; } ;
struct TYPE_4__ {TYPE_1__ r; } ;
struct s_zstate {int zs_in_count; int /*<<< orphan*/ * zs_fp; TYPE_2__ u; scalar_t__ zs_out_count; int /*<<< orphan*/  zs_checkpoint; scalar_t__ zs_ratio; scalar_t__ zs_clear_flg; int /*<<< orphan*/  zs_block_compress; scalar_t__ zs_free_ent; int /*<<< orphan*/  zs_hsize; int /*<<< orphan*/  zs_state; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_MASK ; 
 int /*<<< orphan*/  CHECK_GAP ; 
 int /*<<< orphan*/  HSIZE ; 
 int /*<<< orphan*/  S_START ; 
 struct s_zstate* calloc (int,int) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  free (struct s_zstate*) ; 
 int /*<<< orphan*/ * funopen (struct s_zstate*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zclose ; 
 int /*<<< orphan*/  zread ; 

FILE *
zdopen(int fd)
{
	struct s_zstate *zs;

	if ((zs = calloc(1, sizeof(struct s_zstate))) == NULL)
		return (NULL);

	zs->zs_state = S_START;

	/* XXX we can get rid of some of these */
	zs->zs_hsize = HSIZE;			/* For dynamic table sizing. */
	zs->zs_free_ent = 0;			/* First unused entry. */
	zs->zs_block_compress = BLOCK_MASK;
	zs->zs_clear_flg = 0;			/* XXX we calloc()'d this structure why = 0? */
	zs->zs_ratio = 0;
	zs->zs_checkpoint = CHECK_GAP;
	zs->zs_in_count = 1;			/* Length of input. */
	zs->zs_out_count = 0;			/* # of codes output (for debugging). */
	zs->u.r.zs_roffset = 0;
	zs->u.r.zs_size = 0;

	/*
	 * Layering compress on top of stdio in order to provide buffering,
	 * and ensure that reads and write work with the data specified.
	 */
	if ((zs->zs_fp = fdopen(fd, "r")) == NULL) {
		free(zs);
		return NULL;
	}

	return funopen(zs, zread, NULL, NULL, zclose);
}
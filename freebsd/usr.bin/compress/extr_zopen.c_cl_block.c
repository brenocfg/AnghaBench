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
struct s_zstate {int dummy; } ;
typedef  int /*<<< orphan*/  count_int ;
typedef  int /*<<< orphan*/  code_int ;

/* Variables and functions */
 scalar_t__ CHECK_GAP ; 
 scalar_t__ CLEAR ; 
 int /*<<< orphan*/  FIRST ; 
 int bytes_out ; 
 scalar_t__ checkpoint ; 
 int /*<<< orphan*/  cl_hash (struct s_zstate*,int /*<<< orphan*/ ) ; 
 int clear_flg ; 
 int /*<<< orphan*/  free_ent ; 
 scalar_t__ hsize ; 
 int in_count ; 
 int output (struct s_zstate*,int /*<<< orphan*/ ) ; 
 long ratio ; 

__attribute__((used)) static int
cl_block(struct s_zstate *zs)		/* Table clear for block compress. */
{
	long rat;

	checkpoint = in_count + CHECK_GAP;

	if (in_count > 0x007fffff) {	/* Shift will overflow. */
		rat = bytes_out >> 8;
		if (rat == 0)		/* Don't divide by zero. */
			rat = 0x7fffffff;
		else
			rat = in_count / rat;
	} else
		rat = (in_count << 8) / bytes_out;	/* 8 fractional bits. */
	if (rat > ratio)
		ratio = rat;
	else {
		ratio = 0;
		cl_hash(zs, (count_int) hsize);
		free_ent = FIRST;
		clear_flg = 1;
		if (output(zs, (code_int) CLEAR) == -1)
			return (-1);
	}
	return (0);
}
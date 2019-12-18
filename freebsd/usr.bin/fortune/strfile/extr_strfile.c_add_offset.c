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
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  beoff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC (int /*<<< orphan*/ *,int) ; 
 int Num_pts ; 
 int /*<<< orphan*/  STORING_PTRS ; 
 int /*<<< orphan*/ * Seekpts ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htobe64 (int /*<<< orphan*/ ) ; 

void
add_offset(FILE *fp, off_t off)
{
	off_t beoff;

	if (!STORING_PTRS) {
		beoff = htobe64(off);
		fwrite(&beoff, 1, sizeof(beoff), fp);
	} else {
		ALLOC(Seekpts, Num_pts + 1);
		Seekpts[Num_pts] = off;
	}
	Num_pts++;
}
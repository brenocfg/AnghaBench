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
struct stat32 {int /*<<< orphan*/  st_spare; scalar_t__ st_btim_ext; scalar_t__ st_ctim_ext; scalar_t__ st_mtim_ext; scalar_t__ st_atim_ext; scalar_t__ st_padding1; scalar_t__ st_padding0; } ;
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP (struct stat,struct stat32,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_CP (struct stat,struct stat32,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  st_atim ; 
 int /*<<< orphan*/  st_birthtim ; 
 int /*<<< orphan*/  st_blksize ; 
 int /*<<< orphan*/  st_blocks ; 
 int /*<<< orphan*/  st_ctim ; 
 int /*<<< orphan*/  st_dev ; 
 int /*<<< orphan*/  st_flags ; 
 int /*<<< orphan*/  st_gen ; 
 int /*<<< orphan*/  st_gid ; 
 int /*<<< orphan*/  st_ino ; 
 int /*<<< orphan*/  st_mode ; 
 int /*<<< orphan*/  st_mtim ; 
 int /*<<< orphan*/  st_nlink ; 
 int /*<<< orphan*/  st_rdev ; 
 int /*<<< orphan*/  st_size ; 
 int /*<<< orphan*/  st_uid ; 

__attribute__((used)) static void
copy_stat(struct stat *in, struct stat32 *out)
{

	CP(*in, *out, st_dev);
	CP(*in, *out, st_ino);
	CP(*in, *out, st_mode);
	CP(*in, *out, st_nlink);
	CP(*in, *out, st_uid);
	CP(*in, *out, st_gid);
	CP(*in, *out, st_rdev);
	TS_CP(*in, *out, st_atim);
	TS_CP(*in, *out, st_mtim);
	TS_CP(*in, *out, st_ctim);
	CP(*in, *out, st_size);
	CP(*in, *out, st_blocks);
	CP(*in, *out, st_blksize);
	CP(*in, *out, st_flags);
	CP(*in, *out, st_gen);
	TS_CP(*in, *out, st_birthtim);
	out->st_padding0 = 0;
	out->st_padding1 = 0;
#ifdef __STAT32_TIME_T_EXT
	out->st_atim_ext = 0;
	out->st_mtim_ext = 0;
	out->st_ctim_ext = 0;
	out->st_btim_ext = 0;
#endif
	bzero(out->st_spare, sizeof(out->st_spare));
}
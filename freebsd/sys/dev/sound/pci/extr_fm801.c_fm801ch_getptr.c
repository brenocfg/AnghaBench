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
typedef  scalar_t__ u_int32_t ;
struct fm801_info {int play_flip; int rec_flip; scalar_t__ rec_start; scalar_t__ play_start; } ;
struct fm801_chinfo {scalar_t__ dir; struct fm801_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  FM_PLAY_DMABUF1 ; 
 int /*<<< orphan*/  FM_PLAY_DMABUF2 ; 
 int /*<<< orphan*/  FM_REC_DMABUF1 ; 
 int /*<<< orphan*/  FM_REC_DMABUF2 ; 
 scalar_t__ PCMDIR_PLAY ; 
 scalar_t__ PCMDIR_REC ; 
 scalar_t__ fm801_rd (struct fm801_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u_int32_t
fm801ch_getptr(kobj_t obj, void *data)
{
	struct fm801_chinfo *ch = data;
	struct fm801_info *fm801 = ch->parent;
	u_int32_t result = 0;

	if (ch->dir == PCMDIR_PLAY) {
		result = fm801_rd(fm801,
			(fm801->play_flip&1) ?
			FM_PLAY_DMABUF2:FM_PLAY_DMABUF1, 4) - fm801->play_start;
	}

	if (ch->dir == PCMDIR_REC) {
		result = fm801_rd(fm801,
			(fm801->rec_flip&1) ?
			FM_REC_DMABUF2:FM_REC_DMABUF1, 4) - fm801->rec_start;
	}

	return result;
}
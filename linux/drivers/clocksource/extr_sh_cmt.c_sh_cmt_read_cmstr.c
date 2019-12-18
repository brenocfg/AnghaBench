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
typedef  int /*<<< orphan*/  u32 ;
struct sh_cmt_channel {TYPE_2__* cmt; scalar_t__ iostart; } ;
struct TYPE_4__ {scalar_t__ mapbase; TYPE_1__* info; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_control ) (scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 sh_cmt_read_cmstr(struct sh_cmt_channel *ch)
{
	if (ch->iostart)
		return ch->cmt->info->read_control(ch->iostart, 0);
	else
		return ch->cmt->info->read_control(ch->cmt->mapbase, 0);
}
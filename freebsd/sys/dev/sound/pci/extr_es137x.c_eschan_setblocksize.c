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
typedef  int /*<<< orphan*/  uint32_t ;
struct es_info {int /*<<< orphan*/  blkcnt; } ;
struct es_chinfo {int /*<<< orphan*/  blksz; struct es_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  eschan_setfragments (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
eschan_setblocksize(kobj_t obj, void *data, uint32_t blksz)
{
  	struct es_chinfo *ch = data;
  	struct es_info *es = ch->parent;

	eschan_setfragments(obj, data, blksz, es->blkcnt);

	return (ch->blksz);
}
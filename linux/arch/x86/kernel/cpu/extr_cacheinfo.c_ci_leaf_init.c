#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct cacheinfo {int /*<<< orphan*/  priv; scalar_t__ physical_line_partition; scalar_t__ number_of_sets; int /*<<< orphan*/  size; scalar_t__ ways_of_associativity; scalar_t__ coherency_line_size; int /*<<< orphan*/  type; int /*<<< orphan*/  level; int /*<<< orphan*/  attributes; int /*<<< orphan*/  id; } ;
struct TYPE_11__ {scalar_t__ physical_line_partition; scalar_t__ ways_of_associativity; scalar_t__ coherency_line_size; } ;
struct TYPE_12__ {TYPE_5__ split; } ;
struct TYPE_9__ {scalar_t__ number_of_sets; } ;
struct TYPE_10__ {TYPE_3__ split; } ;
struct TYPE_7__ {size_t type; int /*<<< orphan*/  level; } ;
struct TYPE_8__ {TYPE_1__ split; } ;
struct _cpuid4_info_regs {int /*<<< orphan*/  nb; TYPE_6__ ebx; TYPE_4__ ecx; int /*<<< orphan*/  size; TYPE_2__ eax; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_ID ; 
 int /*<<< orphan*/ * cache_type_map ; 

__attribute__((used)) static void ci_leaf_init(struct cacheinfo *this_leaf,
			 struct _cpuid4_info_regs *base)
{
	this_leaf->id = base->id;
	this_leaf->attributes = CACHE_ID;
	this_leaf->level = base->eax.split.level;
	this_leaf->type = cache_type_map[base->eax.split.type];
	this_leaf->coherency_line_size =
				base->ebx.split.coherency_line_size + 1;
	this_leaf->ways_of_associativity =
				base->ebx.split.ways_of_associativity + 1;
	this_leaf->size = base->size;
	this_leaf->number_of_sets = base->ecx.split.number_of_sets + 1;
	this_leaf->physical_line_partition =
				base->ebx.split.physical_line_partition + 1;
	this_leaf->priv = base->nb;
}
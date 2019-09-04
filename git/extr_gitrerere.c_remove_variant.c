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
struct rerere_id {size_t variant; TYPE_1__* collection; } ;
struct TYPE_2__ {scalar_t__* status; } ;

/* Variables and functions */
 int /*<<< orphan*/  rerere_path (struct rerere_id*,char*) ; 
 int /*<<< orphan*/  unlink_or_warn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_variant(struct rerere_id *id)
{
	unlink_or_warn(rerere_path(id, "postimage"));
	unlink_or_warn(rerere_path(id, "preimage"));
	id->collection->status[id->variant] = 0;
}
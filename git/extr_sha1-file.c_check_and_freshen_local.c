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
struct object_id {int dummy; } ;
struct TYPE_4__ {TYPE_1__* objects; } ;
struct TYPE_3__ {int /*<<< orphan*/  odb; } ;

/* Variables and functions */
 int check_and_freshen_odb (int /*<<< orphan*/ ,struct object_id const*,int) ; 
 TYPE_2__* the_repository ; 

__attribute__((used)) static int check_and_freshen_local(const struct object_id *oid, int freshen)
{
	return check_and_freshen_odb(the_repository->objects->odb, oid, freshen);
}
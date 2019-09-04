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
struct repository {TYPE_1__* objects; } ;
struct packed_git {int dummy; } ;
struct TYPE_2__ {struct packed_git* packed_git; } ;

/* Variables and functions */
 int /*<<< orphan*/  prepare_packed_git (struct repository*) ; 

struct packed_git *get_packed_git(struct repository *r)
{
	prepare_packed_git(r);
	return r->objects->packed_git;
}
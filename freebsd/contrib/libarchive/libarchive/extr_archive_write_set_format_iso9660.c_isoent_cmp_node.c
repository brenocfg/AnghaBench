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
struct isoent {TYPE_2__* file; } ;
struct archive_rb_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  s; } ;
struct TYPE_4__ {TYPE_1__ basename; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isoent_cmp_node(const struct archive_rb_node *n1,
    const struct archive_rb_node *n2)
{
	const struct isoent *e1 = (const struct isoent *)n1;
	const struct isoent *e2 = (const struct isoent *)n2;

	return (strcmp(e1->file->basename.s, e2->file->basename.s));
}
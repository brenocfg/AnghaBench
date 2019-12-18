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
struct strbuf {int dummy; } ;
struct repository {TYPE_1__* objects; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  odb; } ;

/* Variables and functions */
 char const* odb_loose_path (int /*<<< orphan*/ ,struct strbuf*,struct object_id const*) ; 

const char *loose_object_path(struct repository *r, struct strbuf *buf,
			      const struct object_id *oid)
{
	return odb_loose_path(r->objects->odb, buf, oid);
}
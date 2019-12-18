#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  names; } ;
typedef  TYPE_1__ Obj_Entry ;
typedef  TYPE_2__ Name_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
object_add_name(Obj_Entry *obj, const char *name)
{
    Name_Entry *entry;
    size_t len;

    len = strlen(name);
    entry = malloc(sizeof(Name_Entry) + len);

    if (entry != NULL) {
	strcpy(entry->name, name);
	STAILQ_INSERT_TAIL(&obj->names, entry, link);
    }
}
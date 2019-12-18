#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int z_interpose; } ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  LD_UTRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UTRACE_PRELOAD_FINISHED ; 
 char* ld_preload ; 
 TYPE_1__* load_object (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t strcspn (char*,char const*) ; 
 int /*<<< orphan*/  strspn (char*,char const*) ; 

__attribute__((used)) static int
load_preload_objects(void)
{
    char *p = ld_preload;
    Obj_Entry *obj;
    static const char delim[] = " \t:;";

    if (p == NULL)
	return 0;

    p += strspn(p, delim);
    while (*p != '\0') {
	size_t len = strcspn(p, delim);
	char savech;

	savech = p[len];
	p[len] = '\0';
	obj = load_object(p, -1, NULL, 0);
	if (obj == NULL)
	    return -1;	/* XXX - cleanup */
	obj->z_interpose = true;
	p[len] = savech;
	p += len;
	p += strspn(p, delim);
    }
    LD_UTRACE(UTRACE_PRELOAD_FINISHED, NULL, NULL, 0, 0, NULL);
    return 0;
}
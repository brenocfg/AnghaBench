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
struct grep_source {int type; int /*<<< orphan*/ * identifier; int /*<<< orphan*/ * driver; scalar_t__ size; int /*<<< orphan*/ * buf; void* path; void* name; } ;
typedef  enum grep_source_type { ____Placeholder_grep_source_type } grep_source_type ;

/* Variables and functions */
#define  GREP_SOURCE_BUF 130 
#define  GREP_SOURCE_FILE 129 
#define  GREP_SOURCE_OID 128 
 int /*<<< orphan*/ * oiddup (void const*) ; 
 int /*<<< orphan*/ * xstrdup (void const*) ; 
 void* xstrdup_or_null (char const*) ; 

void grep_source_init(struct grep_source *gs, enum grep_source_type type,
		      const char *name, const char *path,
		      const void *identifier)
{
	gs->type = type;
	gs->name = xstrdup_or_null(name);
	gs->path = xstrdup_or_null(path);
	gs->buf = NULL;
	gs->size = 0;
	gs->driver = NULL;

	switch (type) {
	case GREP_SOURCE_FILE:
		gs->identifier = xstrdup(identifier);
		break;
	case GREP_SOURCE_OID:
		gs->identifier = oiddup(identifier);
		break;
	case GREP_SOURCE_BUF:
		gs->identifier = NULL;
		break;
	}
}
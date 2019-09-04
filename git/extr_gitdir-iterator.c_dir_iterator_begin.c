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
struct dir_iterator {int /*<<< orphan*/  path; } ;
struct dir_iterator_int {int levels_nr; TYPE_1__* levels; int /*<<< orphan*/  levels_alloc; struct dir_iterator base; } ;
struct TYPE_2__ {scalar_t__ initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  strbuf_addstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dir_iterator_int* xcalloc (int,int) ; 

struct dir_iterator *dir_iterator_begin(const char *path)
{
	struct dir_iterator_int *iter = xcalloc(1, sizeof(*iter));
	struct dir_iterator *dir_iterator = &iter->base;

	if (!path || !*path)
		BUG("empty path passed to dir_iterator_begin()");

	strbuf_init(&iter->base.path, PATH_MAX);
	strbuf_addstr(&iter->base.path, path);

	ALLOC_GROW(iter->levels, 10, iter->levels_alloc);

	iter->levels_nr = 1;
	iter->levels[0].initialized = 0;

	return dir_iterator;
}
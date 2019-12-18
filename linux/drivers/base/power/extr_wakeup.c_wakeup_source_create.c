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
struct wakeup_source {char const* name; int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ida_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wakeup_source*) ; 
 int /*<<< orphan*/  kfree_const (char const*) ; 
 char* kstrdup_const (char const*,int /*<<< orphan*/ ) ; 
 struct wakeup_source* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup_ida ; 

struct wakeup_source *wakeup_source_create(const char *name)
{
	struct wakeup_source *ws;
	const char *ws_name;
	int id;

	ws = kzalloc(sizeof(*ws), GFP_KERNEL);
	if (!ws)
		goto err_ws;

	ws_name = kstrdup_const(name, GFP_KERNEL);
	if (!ws_name)
		goto err_name;
	ws->name = ws_name;

	id = ida_alloc(&wakeup_ida, GFP_KERNEL);
	if (id < 0)
		goto err_id;
	ws->id = id;

	return ws;

err_id:
	kfree_const(ws->name);
err_name:
	kfree(ws);
err_ws:
	return NULL;
}
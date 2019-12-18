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
struct walker_data {int got_alternates; TYPE_1__* alt; } ;
struct walker {struct walker_data* data; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  prefetch; int /*<<< orphan*/  fetch_ref; int /*<<< orphan*/  fetch; scalar_t__ corrupt_object_found; } ;
struct TYPE_2__ {char* base; int /*<<< orphan*/ * next; int /*<<< orphan*/ * packs; scalar_t__ got_indices; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_fill_function (struct walker*,int (*) (void*)) ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  fetch ; 
 int /*<<< orphan*/  fetch_ref ; 
 scalar_t__ fill_active_slot ; 
 int /*<<< orphan*/  prefetch ; 
 int strlen (char*) ; 
 void* xmalloc (int) ; 
 char* xstrdup (char const*) ; 

struct walker *get_http_walker(const char *url)
{
	char *s;
	struct walker_data *data = xmalloc(sizeof(struct walker_data));
	struct walker *walker = xmalloc(sizeof(struct walker));

	data->alt = xmalloc(sizeof(*data->alt));
	data->alt->base = xstrdup(url);
	for (s = data->alt->base + strlen(data->alt->base) - 1; *s == '/'; --s)
		*s = 0;

	data->alt->got_indices = 0;
	data->alt->packs = NULL;
	data->alt->next = NULL;
	data->got_alternates = -1;

	walker->corrupt_object_found = 0;
	walker->fetch = fetch;
	walker->fetch_ref = fetch_ref;
	walker->prefetch = prefetch;
	walker->cleanup = cleanup;
	walker->data = data;

#ifdef USE_CURL_MULTI
	add_fill_function(walker, (int (*)(void *)) fill_active_slot);
#endif

	return walker;
}
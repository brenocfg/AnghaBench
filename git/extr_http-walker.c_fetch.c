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
struct walker_data {struct alt_base* alt; } ;
struct walker {struct walker_data* data; } ;
struct alt_base {char* base; struct alt_base* next; } ;

/* Variables and functions */
 int error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fetch_alternates (struct walker*,char*) ; 
 int /*<<< orphan*/  fetch_object (struct walker*,unsigned char*) ; 
 int /*<<< orphan*/  hash_to_hex (unsigned char*) ; 
 int /*<<< orphan*/  http_fetch_pack (struct walker*,struct alt_base*,unsigned char*) ; 

__attribute__((used)) static int fetch(struct walker *walker, unsigned char *hash)
{
	struct walker_data *data = walker->data;
	struct alt_base *altbase = data->alt;

	if (!fetch_object(walker, hash))
		return 0;
	while (altbase) {
		if (!http_fetch_pack(walker, altbase, hash))
			return 0;
		fetch_alternates(walker, data->alt->base);
		altbase = altbase->next;
	}
	return error("Unable to find %s under %s", hash_to_hex(hash),
		     data->alt->base);
}
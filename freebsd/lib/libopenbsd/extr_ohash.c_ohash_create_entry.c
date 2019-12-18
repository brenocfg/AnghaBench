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
struct ohash_info {char* (* alloc ) (int,int /*<<< orphan*/ ) ;int key_offset; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 char* stub1 (int,int /*<<< orphan*/ ) ; 

void *
ohash_create_entry(struct ohash_info *i, const char *start, const char **end)
{
	char *p;

	if (!*end)
		*end = start + strlen(start);
	p = (i->alloc)(i->key_offset + (*end - start) + 1, i->data);
	if (p) {
		memcpy(p+i->key_offset, start, *end-start);
		p[i->key_offset + (*end - start)] = '\0';
	}
	return (void *)p;
}
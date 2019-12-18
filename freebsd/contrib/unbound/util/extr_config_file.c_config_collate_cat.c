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
struct config_strlist {char* str; struct config_strlist* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

char*
config_collate_cat(struct config_strlist* list)
{
	size_t total = 0, left;
	struct config_strlist* s;
	char *r, *w;
	if(!list) /* no elements */
		return strdup("");
	if(list->next == NULL) /* one element , no newline at end. */
		return strdup(list->str);
	/* count total length */
	for(s=list; s; s=s->next)
		total += strlen(s->str) + 1; /* len + newline */
	left = total+1; /* one extra for nul at end */
	r = malloc(left); 
	if(!r)
		return NULL;
	w = r;
	for(s=list; s; s=s->next) {
		size_t this = strlen(s->str);
		if(this+2 > left) { /* sanity check */
			free(r);
			return NULL;
		}
		snprintf(w, left, "%s\n", s->str);
		this = strlen(w);
		w += this;
		left -= this;
	}
	return r;
}
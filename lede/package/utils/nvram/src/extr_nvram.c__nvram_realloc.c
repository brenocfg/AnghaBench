#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; char* value; } ;
typedef  TYPE_1__ nvram_tuple_t ;
struct TYPE_8__ {int length; int offset; } ;
typedef  TYPE_2__ nvram_handle_t ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 
 scalar_t__ realloc (char*,int) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static nvram_tuple_t * _nvram_realloc( nvram_handle_t *h, nvram_tuple_t *t,
	const char *name, const char *value )
{
	if ((strlen(value) + 1) > h->length - h->offset)
		return NULL;

	if (!t) {
		if (!(t = malloc(sizeof(nvram_tuple_t) + strlen(name) + 1)))
			return NULL;

		/* Copy name */
		t->name = (char *) &t[1];
		strcpy(t->name, name);

		t->value = NULL;
	}

	/* Copy value */
	if (!t->value || strcmp(t->value, value))
	{
		if(!(t->value = (char *) realloc(t->value, strlen(value)+1)))
			return NULL;

		strcpy(t->value, value);
		t->value[strlen(value)] = '\0';
	}

	return t;
}
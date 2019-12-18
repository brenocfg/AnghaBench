#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct _property {int dummy; } ;
typedef  TYPE_1__* properties ;
struct TYPE_4__ {int /*<<< orphan*/ * value; struct TYPE_4__* name; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 void* strdup (char*) ; 

__attribute__((used)) static properties
property_alloc(char *name, char *value)
{
    properties n;

    if ((n = (properties)malloc(sizeof(struct _property))) == NULL)
	return (NULL);
    n->next = NULL;
    if (name != NULL) {
	if ((n->name = strdup(name)) == NULL) {
	    free(n);
	    return (NULL);
	}
    } else
	n->name = NULL;
    if (value != NULL) {
	if ((n->value = strdup(value)) == NULL) {
	    free(n->name);
	    free(n);
	    return (NULL);
	}
    } else
	n->value = NULL;
    return (n);
}
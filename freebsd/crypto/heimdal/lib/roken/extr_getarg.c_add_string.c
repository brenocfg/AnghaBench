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
struct TYPE_3__ {char** strings; int num_strings; } ;
typedef  TYPE_1__ getarg_strings ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  free (char**) ; 
 char** realloc (char**,int) ; 

__attribute__((used)) static int
add_string(getarg_strings *s, char *value)
{
    char **strings;

    strings = realloc(s->strings, (s->num_strings + 1) * sizeof(*s->strings));
    if (strings == NULL) {
	free(s->strings);
	s->strings = NULL;
	s->num_strings = 0;
	return ENOMEM;
    }
    s->strings = strings;
    s->strings[s->num_strings] = value;
    s->num_strings++;
    return 0;
}
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
struct getarg_strings {int num_strings; char** strings; } ;

/* Variables and functions */
 char** ecalloc (int,int) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  permute (char****,size_t*,char**,int /*<<< orphan*/ ,int) ; 

char ***
permutate_all(struct getarg_strings *strings, size_t *size)
{
    char **list, ***all = NULL;
    int i;

    *size = 0;

    list = ecalloc(strings->num_strings, sizeof(*list));
    for (i = 0; i < strings->num_strings; i++)
	list[i] = strings->strings[i];

    permute(&all, size, list, 0, strings->num_strings);
    free(list);
    return all;
}
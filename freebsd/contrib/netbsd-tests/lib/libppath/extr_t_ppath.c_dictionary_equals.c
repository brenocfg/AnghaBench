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
typedef  int /*<<< orphan*/  prop_dictionary_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* prop_dictionary_externalize (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static bool
dictionary_equals(prop_dictionary_t ld, prop_dictionary_t rd)
{
	bool eq;
	char *lt, *rt;

	lt = prop_dictionary_externalize(ld);
	rt = prop_dictionary_externalize(rd);

	assert(lt != NULL && rt != NULL);

	eq = (strcmp(lt, rt) == 0);

	free(lt);
	free(rt);

	return eq;
}
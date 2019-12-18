#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kadm5_pw_policy_check_func {char* name; } ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_4__ {struct kadm5_pw_policy_check_func* funcs; } ;
struct TYPE_3__ {char* name; struct kadm5_pw_policy_check_func* funcs; } ;

/* Variables and functions */
 TYPE_2__ builtin_verifier ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int num_verifiers ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 TYPE_1__** verifiers ; 

__attribute__((used)) static const struct kadm5_pw_policy_check_func *
find_func(krb5_context context, const char *name)
{
    const struct kadm5_pw_policy_check_func *f;
    char *module = NULL;
    const char *p, *func;
    int i;

    p = strchr(name, ':');
    if (p) {
	size_t len = p - name + 1;
	func = p + 1;
	module = malloc(len);
	if (module == NULL)
	    return NULL;
	strlcpy(module, name, len);
    } else
	func = name;

    /* Find module in loaded modules first */
    for (i = 0; i < num_verifiers; i++) {
	if (module && strcmp(module, verifiers[i]->name) != 0)
	    continue;
	for (f = verifiers[i]->funcs; f->name ; f++)
	    if (strcmp(func, f->name) == 0) {
		if (module)
		    free(module);
		return f;
	    }
    }
    /* Lets try try the builtin modules */
    if (module == NULL || strcmp(module, "builtin") == 0) {
	for (f = builtin_verifier.funcs; f->name ; f++)
	    if (strcmp(func, f->name) == 0) {
		if (module)
		    free(module);
		return f;
	    }
    }
    if (module)
	free(module);
    return NULL;
}
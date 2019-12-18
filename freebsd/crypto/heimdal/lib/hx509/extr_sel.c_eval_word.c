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
struct hx_expr {int op; char const* arg1; struct hx_expr* arg2; } ;
typedef  int /*<<< orphan*/ * hx509_env ;
typedef  int /*<<< orphan*/  hx509_context ;

/* Variables and functions */
#define  expr_STRING 129 
#define  expr_VAR 128 
 char const* hx509_env_find (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * hx509_env_find_binding (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static const char *
eval_word(hx509_context context, hx509_env env, struct hx_expr *word)
{
    switch (word->op) {
    case expr_STRING:
	return word->arg1;
    case expr_VAR:
	if (word->arg2 == NULL)
	    return hx509_env_find(context, env, word->arg1);

	env = hx509_env_find_binding(context, env, word->arg1);
	if (env == NULL)
	    return NULL;

	return eval_word(context, env, word->arg2);
    default:
	return NULL;
    }
}
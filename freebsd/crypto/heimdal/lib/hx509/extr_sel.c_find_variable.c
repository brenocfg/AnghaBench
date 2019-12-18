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
struct hx_expr {scalar_t__ op; struct hx_expr* arg2; int /*<<< orphan*/  arg1; } ;
typedef  int /*<<< orphan*/ * hx509_env ;
typedef  int /*<<< orphan*/  hx509_context ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ expr_VAR ; 
 int /*<<< orphan*/ * hx509_env_find_binding (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static hx509_env
find_variable(hx509_context context, hx509_env env, struct hx_expr *word)
{
    assert(word->op == expr_VAR);

    if (word->arg2 == NULL)
	return hx509_env_find_binding(context, env, word->arg1);

    env = hx509_env_find_binding(context, env, word->arg1);
    if (env == NULL)
	return NULL;
    return find_variable(context, env, word->arg2);
}
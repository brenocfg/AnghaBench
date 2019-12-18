#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sbcset; int /*<<< orphan*/  mbcset; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ duplicated; TYPE_1__ opr; } ;
typedef  TYPE_2__ re_token_t ;

/* Variables and functions */
 scalar_t__ COMPLEX_BRACKET ; 
 scalar_t__ SIMPLE_BRACKET ; 
 int /*<<< orphan*/  free_charset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  re_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_token (re_token_t *node)
{
#ifdef RE_ENABLE_I18N
  if (node->type == COMPLEX_BRACKET && node->duplicated == 0)
    free_charset (node->opr.mbcset);
  else
#endif /* RE_ENABLE_I18N */
    if (node->type == SIMPLE_BRACKET && node->duplicated == 0)
      re_free (node->opr.sbcset);
}
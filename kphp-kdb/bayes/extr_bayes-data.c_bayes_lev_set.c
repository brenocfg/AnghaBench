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
struct lev_bayes_set {int type; int /*<<< orphan*/  text_len; int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int bayes_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int bayes_lev_set (struct lev_bayes_set *E) {
  return bayes_set (E->text, E->text_len, E->type & 15);
}
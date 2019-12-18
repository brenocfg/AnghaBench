#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ token; } ;
struct TYPE_7__ {TYPE_1__ t; } ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
 scalar_t__ TK_RETURN ; 
 int /*<<< orphan*/  block_follow (TYPE_2__*,int) ; 
 int /*<<< orphan*/  statement (TYPE_2__*) ; 

__attribute__((used)) static void statlist (LexState *ls) {
  /* statlist -> { stat [`;'] } */
  while (!block_follow(ls, 1)) {
    if (ls->t.token == TK_RETURN) {
      statement(ls);
      return;  /* 'return' must be last statement */
    }
    statement(ls);
  }
}
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
struct TYPE_3__ {int /*<<< orphan*/  rowSepPrior; int /*<<< orphan*/  rowSeparator; int /*<<< orphan*/  colSepPrior; int /*<<< orphan*/  colSeparator; int /*<<< orphan*/  modePrior; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void outputModePop(ShellState *p){
  p->mode = p->modePrior;
  memcpy(p->colSeparator, p->colSepPrior, sizeof(p->colSeparator));
  memcpy(p->rowSeparator, p->rowSepPrior, sizeof(p->rowSeparator));
}
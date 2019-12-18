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
struct TYPE_3__ {int /*<<< orphan*/  rowSeparator; int /*<<< orphan*/  rowSepPrior; int /*<<< orphan*/  colSeparator; int /*<<< orphan*/  colSepPrior; int /*<<< orphan*/  mode; int /*<<< orphan*/  modePrior; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void outputModePush(ShellState *p){
  p->modePrior = p->mode;
  memcpy(p->colSepPrior, p->colSeparator, sizeof(p->colSeparator));
  memcpy(p->rowSepPrior, p->rowSeparator, sizeof(p->rowSeparator));
}
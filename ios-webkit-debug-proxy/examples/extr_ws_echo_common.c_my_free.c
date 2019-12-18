#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct my_struct {int dummy; } ;
typedef  TYPE_1__* my_t ;
struct TYPE_5__ {int /*<<< orphan*/  ws; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ws_free (int /*<<< orphan*/ ) ; 

void my_free(my_t my) {
  if (my) {
    ws_free(my->ws);
    memset(my, 0, sizeof(struct my_struct));
    free(my);
  }
}
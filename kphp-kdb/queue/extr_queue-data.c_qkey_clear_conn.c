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
struct TYPE_3__ {int /*<<< orphan*/ * conn; } ;
typedef  TYPE_1__ qkey ;

/* Variables and functions */
 TYPE_1__* qkey_get (char*,int /*<<< orphan*/ ) ; 

void qkey_clear_conn (char *kname) {
  qkey *k = qkey_get (kname, 0);
  if (k != NULL) {
    k->conn = NULL;
  }
}
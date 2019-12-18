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
struct TYPE_3__ {int /*<<< orphan*/  uniq_nkey; int /*<<< orphan*/ * uniq_key; int /*<<< orphan*/  root_nkey; int /*<<< orphan*/ * root_key; int /*<<< orphan*/ * root; int /*<<< orphan*/  data_nkey; int /*<<< orphan*/ * data_key; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ GKeyData ;

/* Variables and functions */

__attribute__((used)) static void
new_modulekey (GKeyData * kdata)
{
  GKeyData key = {
    .data = NULL,
    .data_key = NULL,
    .data_nkey = 0,
    .root = NULL,
    .root_key = NULL,
    .root_nkey = 0,
    .uniq_key = NULL,
    .uniq_nkey = 0,
  };
  *kdata = key;
}
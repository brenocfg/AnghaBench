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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  GModule ;

/* Variables and functions */
 int /*<<< orphan*/  ht_insert_cumts (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ht_insert_meta_data (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
insert_cumts (int data_nkey, uint64_t ts, GModule module)
{
  ht_insert_cumts (module, data_nkey, ts);
  ht_insert_meta_data (module, "cumts", ts);
}
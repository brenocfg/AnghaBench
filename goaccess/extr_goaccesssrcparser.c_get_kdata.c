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
struct TYPE_3__ {char* data_key; char* data; } ;
typedef  TYPE_1__ GKeyData ;

/* Variables and functions */

__attribute__((used)) static void
get_kdata (GKeyData * kdata, char *data_key, char *data)
{
  /* inserted in keymap */
  kdata->data_key = data_key;
  /* inserted in datamap */
  kdata->data = data;
}
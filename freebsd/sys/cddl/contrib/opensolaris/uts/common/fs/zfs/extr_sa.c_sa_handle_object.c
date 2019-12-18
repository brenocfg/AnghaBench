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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {TYPE_1__* sa_bonus; } ;
typedef  TYPE_2__ sa_handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  db_object; } ;

/* Variables and functions */

uint64_t
sa_handle_object(sa_handle_t *hdl)
{
	return (hdl->sa_bonus->db_object);
}
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
struct TYPE_4__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_id_t ;
struct TYPE_5__ {char const* txn_id; } ;
typedef  TYPE_2__ id_private_t ;

/* Variables and functions */

const char *
svn_fs_base__id_txn_id(const svn_fs_id_t *id)
{
  id_private_t *pvt = id->fsap_data;

  return pvt->txn_id;
}
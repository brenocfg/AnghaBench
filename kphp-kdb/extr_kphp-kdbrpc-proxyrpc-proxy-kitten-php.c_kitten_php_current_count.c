#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rpc_cluster {int dummy; } ;
struct TYPE_2__ {struct rpc_cluster** schema_extra; } ;

/* Variables and functions */
 TYPE_1__* CurConf ; 
 size_t KittenPhpNum ; 
 int tree_count_worker (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  worker_tree ; 

int kitten_php_current_count (void) {
  struct rpc_cluster *C = CurConf->schema_extra[KittenPhpNum];
  if (!C) { 
    return -1; 
  }
  return tree_count_worker (worker_tree);
}
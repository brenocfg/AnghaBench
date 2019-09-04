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
struct TYPE_5__ {int op; } ;
typedef  TYPE_1__ query_node_t ;

/* Variables and functions */
 int MAX_QUERY_NODES ; 
 TYPE_1__* QV ; 
 int Q_nodes ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static query_node_t *new_query_node (int op) {
  query_node_t *X = QV + Q_nodes;
  if (Q_nodes >= MAX_QUERY_NODES) {
    return 0;
  }
  Q_nodes++;
  memset (X, 0, sizeof (*X));
  X->op = op;
  return X;
}
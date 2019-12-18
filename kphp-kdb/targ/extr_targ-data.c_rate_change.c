#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* uplink; } ;
typedef  TYPE_1__ utree_t ;
struct TYPE_12__ {int rate; size_t uid; TYPE_4__* uplink_rate; TYPE_4__* right_rate; TYPE_4__* left_rate; } ;
typedef  TYPE_2__ user_t ;
struct TYPE_14__ {TYPE_1__* uplink; } ;
struct TYPE_13__ {TYPE_1__* right; TYPE_1__* left; } ;

/* Variables and functions */
 int* UserRate ; 
 int lrand48 () ; 
 TYPE_6__* rate_tree ; 
 TYPE_6__* utree_insert_node (TYPE_6__*,TYPE_1__*) ; 
 TYPE_1__* utree_merge (TYPE_4__*,TYPE_4__*) ; 

void rate_change (user_t *U, int new_rate) {
  if (!U) {
    return;
  }

  utree_t *new_tree = utree_merge (U->left_rate, U->right_rate);
  
  if (new_tree) {
    new_tree->uplink = U->uplink_rate;
  }

  //here we require "left" to be the first field of user_t
  //otherwise it will fail at root (be careful with this trick!)
  if (U->uplink_rate->left == (utree_t *)U) {
    U->uplink_rate->left = new_tree;
  } else {
    U->uplink_rate->right = new_tree;
  }

  U->rate = (new_rate << 8) + (lrand48 () & 255);

  U->left_rate = U->right_rate = U->uplink_rate = 0;

  rate_tree = utree_insert_node (rate_tree, (utree_t *)U);
  rate_tree->uplink = (utree_t *)&rate_tree;
  UserRate[U->uid] = new_rate;
}
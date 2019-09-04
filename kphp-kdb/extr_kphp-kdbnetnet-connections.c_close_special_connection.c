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
struct connection {scalar_t__ basic_type; size_t listening; scalar_t__ listening_generation; } ;
struct TYPE_2__ {scalar_t__ basic_type; scalar_t__ generation; } ;

/* Variables and functions */
 TYPE_1__* Connections ; 
 int EVT_LEVEL ; 
 int EVT_RWX ; 
 scalar_t__ active_special_connections ; 
 scalar_t__ ct_listen ; 
 int /*<<< orphan*/  epoll_insert (size_t,int) ; 
 scalar_t__ max_special_connections ; 

void close_special_connection (struct connection *c) {
  if (c->basic_type != ct_listen) {
    if (--active_special_connections < max_special_connections && Connections[c->listening].basic_type == ct_listen && Connections[c->listening].generation == c->listening_generation) {
      epoll_insert (c->listening, EVT_RWX | EVT_LEVEL);
    }
  }
}
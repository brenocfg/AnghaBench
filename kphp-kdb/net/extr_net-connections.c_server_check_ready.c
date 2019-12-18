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
struct connection {scalar_t__ status; int ready; } ;

/* Variables and functions */
 scalar_t__ conn_connecting ; 
 scalar_t__ conn_error ; 
 scalar_t__ conn_none ; 
 scalar_t__ cr_failed ; 
 int cr_notyet ; 
 int cr_ok ; 

int server_check_ready (struct connection *c) {
  if (c->status == conn_none || c->status == conn_connecting) {
    return c->ready = cr_notyet;
  }
  if (c->status == conn_error || c->ready == cr_failed) {
    return c->ready = cr_failed;
  }
  return c->ready = cr_ok;
}
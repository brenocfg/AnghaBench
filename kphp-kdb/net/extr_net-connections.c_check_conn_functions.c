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
struct TYPE_3__ {scalar_t__ magic; char* title; scalar_t__ check_ready; void* flush; void* connected; void* alarm; void* wakeup; void* init_outbound; scalar_t__ writer; int /*<<< orphan*/  parse_execute; scalar_t__ reader; scalar_t__ close; scalar_t__ free_buffers; void* init_accepted; scalar_t__ accept; scalar_t__ run; } ;
typedef  TYPE_1__ conn_type_t ;

/* Variables and functions */
 scalar_t__ CONN_FUNC_MAGIC ; 
 scalar_t__ accept_new_connections ; 
 scalar_t__ free_connection_buffers ; 
 scalar_t__ server_check_ready ; 
 scalar_t__ server_close_connection ; 
 void* server_noop ; 
 scalar_t__ server_read_write ; 
 scalar_t__ server_reader ; 
 scalar_t__ server_writer ; 

int check_conn_functions (conn_type_t *type) {
  if (type->magic != CONN_FUNC_MAGIC) {
    return -1;
  }
  if (!type->title) {
    type->title = "(unknown)";
  }
  if (!type->run) {
    type->run = server_read_write;
  }
  if (!type->accept) {
    type->accept = accept_new_connections;
  }
  if (!type->init_accepted) {
    type->init_accepted = server_noop;
  }
  if (!type->free_buffers) {
    type->free_buffers = free_connection_buffers;
  }
  if (!type->close) {
    type->close = server_close_connection;
  }
  if (!type->reader) {
    type->reader = server_reader;
    if (!type->parse_execute) {
      return -1;
    }
  }
  if (!type->writer) {
    type->writer = server_writer;
  }
  if (!type->init_outbound) {
    type->init_outbound = server_noop;
  }
  if (!type->wakeup) {
    type->wakeup = server_noop;
  }
  if (!type->alarm) {
    type->alarm = server_noop;
  }
  if (!type->connected) {
    type->connected = server_noop;
  }
  if (!type->flush) {
    type->flush = server_noop;
  }
  if (!type->check_ready) {
    type->check_ready = server_check_ready;
  }
  return 0;
}
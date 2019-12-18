#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  fd; } ;
struct TYPE_9__ {int block_size; TYPE_1__ u; } ;
typedef  TYPE_2__ tftp_connection_t ;

/* Variables and functions */
 TYPE_2__** C ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tftp_conn_close_handles (TYPE_2__*) ; 
 int /*<<< orphan*/  tftp_udp_connections ; 
 int /*<<< orphan*/  zfree (TYPE_2__*,int) ; 
 TYPE_2__* zmalloc0 (int) ; 

tftp_connection_t *get_connection_f (int tid, int force) {
  if (tid < 0 || tid > 0xffff) { return NULL; }
  tftp_connection_t *c = C[tid];
  if (!force) { return c; }
  if (force > 0) {
    tftp_udp_connections++;
    c = zmalloc0 (sizeof (tftp_connection_t));
    c->block_size = 512;
    return C[tid] = c;
  }
  assert (force < 0);
  if (c != NULL) {
    tftp_udp_connections--;
    fd_close (&c->u.fd);
    tftp_conn_close_handles (c);
    zfree (c, sizeof (tftp_connection_t));
    C[tid] = NULL;
  }
  return c;
}
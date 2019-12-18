#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct connection {size_t fd; int /*<<< orphan*/  generation; } ;
struct TYPE_4__ {int /*<<< orphan*/  generation; } ;
typedef  TYPE_1__ host_t ;

/* Variables and functions */
 TYPE_1__** CONN_FD_HOST ; 
 size_t MAX_CONNECTIONS ; 
 int /*<<< orphan*/  vkprintf (int,char*,size_t,...) ; 

host_t *get_host_by_connection (struct connection *c) {
  if (c->fd < 0 || c->fd >= MAX_CONNECTIONS) {
    return NULL;
  }
  host_t *H = CONN_FD_HOST[c->fd];
  if (H == NULL) {
    vkprintf (3, "CONN_FD_HOST[%d] = NULL\n", c->fd);
    return NULL;
  }
  if (H->generation != c->generation) {
    vkprintf (3, "H->generation (%d) != c->generation (%d)\n", H->generation, c->generation);
    return CONN_FD_HOST[c->fd] = NULL;
  }
  return H;
}
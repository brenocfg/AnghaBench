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
struct connection {size_t fd; unsigned int remote_ip; int /*<<< orphan*/  generation; } ;
struct TYPE_5__ {unsigned int ip; unsigned long long volume_id; int pid; int /*<<< orphan*/  generation; int /*<<< orphan*/  hostname; scalar_t__ binlog_pos; } ;
typedef  TYPE_1__ host_t ;

/* Variables and functions */
 TYPE_1__** CONN_FD_HOST ; 
 int COPYEXEC_ERR_HOSTNAME_MISMATCHED ; 
 int COPYEXEC_ERR_INVAL ; 
 int COPYEXEC_ERR_VOLUME_ID_MISMATCHED ; 
 int COPYEXEC_RESULT_IP_CHANGED ; 
 int COPYEXEC_RESULT_NEW_HOST ; 
 int COPYEXEC_RESULT_PID_CHANGED ; 
 TYPE_1__* get_host_by_random_tag (unsigned long long,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const* const) ; 
 int /*<<< orphan*/  zstrdup (char const* const) ; 

int get_host_on_connect (struct connection *c, unsigned long long volume_id, unsigned long long random_tag, const char *const hostname, int pid, host_t **R) {
  if (c->fd < 0) {
    return COPYEXEC_ERR_INVAL;
  }
  const unsigned ip = c->remote_ip;
  *R = NULL;
  host_t *H = get_host_by_random_tag (random_tag, 1);
  if (H->ip == 0) {
    H->volume_id = volume_id;
    H->binlog_pos = 0;
    H->hostname = zstrdup (hostname);
    H->ip = ip;
    H->pid = pid;
    H->generation = c->generation;
    CONN_FD_HOST[c->fd] = H;
    *R = H;
    return COPYEXEC_RESULT_NEW_HOST;
  } else {
    if (H->volume_id != volume_id) {
      return COPYEXEC_ERR_VOLUME_ID_MISMATCHED;
    }
    if (strcmp (H->hostname, hostname)) {
      return COPYEXEC_ERR_HOSTNAME_MISMATCHED;
    }
    H->generation = c->generation;
    CONN_FD_HOST[c->fd] = H;
    *R = H;
    if (H->ip != ip) {
      H->ip = ip;
      H->pid = pid;
      return COPYEXEC_RESULT_IP_CHANGED;
    }
    if (H->pid != pid) {
      H->pid = pid;
      return COPYEXEC_RESULT_PID_CHANGED;
    }
    return 0;
  }
}
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
struct rpc_server {int status; scalar_t__ retry_interval; scalar_t__ failed; scalar_t__ last_received_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rpc_connect_open (struct rpc_server*,char**,int*) ; 
 char* estrdup (char*) ; 
 scalar_t__ ping_timeout ; 
 scalar_t__ precise_now ; 
 int /*<<< orphan*/  rpc_ping (struct rpc_server*) ; 
#define  rpc_status_connected 130 
#define  rpc_status_disconnected 129 
#define  rpc_status_failed 128 
 int /*<<< orphan*/  update_precise_now () ; 

__attribute__((used)) static int rpc_open (struct rpc_server *server, char **error_string, int *errnum) { /* {{{ */
  switch (server->status) {
    case rpc_status_disconnected:
      if (_rpc_connect_open (server, error_string, errnum) > 0) {
        return 1;
      } else {
        break;
      }
    
    case rpc_status_connected:
      update_precise_now ();
      if (precise_now - server->last_received_time > ping_timeout) {
        if (rpc_ping (server) > 0) {
          return 1;
        } else if (_rpc_connect_open (server, error_string, errnum) > 0) {
          return 1;
        } else {
          break;
        }
      } else {
        return 1;
      }


    case rpc_status_failed:
      update_precise_now ();
      if (server->retry_interval >= 0 && precise_now >= server->failed + server->retry_interval) {
        if (_rpc_connect_open (server, error_string, errnum) > 0) {
          return 1;
        }
      } else {
        if (error_string) {
          *error_string = estrdup ("server failed some time ago. Fail timeout not exceeded.");
          *errnum = 0;
        }
        break;
      }
      break;
  }
  return -1;
}
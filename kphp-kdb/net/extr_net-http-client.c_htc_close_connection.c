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
struct connection {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* htc_close ) (struct connection*,int) ;} ;

/* Variables and functions */
 TYPE_1__* HTC_FUNC (struct connection*) ; 
 int client_close_connection (struct connection*,int) ; 
 int /*<<< orphan*/  outbound_http_connections ; 
 int /*<<< orphan*/  server_reader (struct connection*) ; 
 int /*<<< orphan*/  stub1 (struct connection*,int) ; 

int htc_close_connection (struct connection *c, int who) {
  outbound_http_connections--;
  
  server_reader (c);

  if (HTC_FUNC(c)->htc_close != NULL) {
    HTC_FUNC(c)->htc_close (c, who);
  } 

  return client_close_connection (c, who);
}
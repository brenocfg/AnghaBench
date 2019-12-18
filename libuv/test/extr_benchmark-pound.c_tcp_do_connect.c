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
typedef  int /*<<< orphan*/  make_connect_fn ;
typedef  int /*<<< orphan*/  conn_rec ;
struct TYPE_2__ {int /*<<< orphan*/  make_connect; } ;

/* Variables and functions */
 TYPE_1__* tcp_conns ; 
 int /*<<< orphan*/  tcp_make_connect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tcp_do_connect(int num, make_connect_fn make_connect, void* arg) {
  int i;

  for (i = 0; i < num; i++) {
    tcp_make_connect((conn_rec*)&tcp_conns[i]);
    tcp_conns[i].make_connect = make_connect;
  }

  return 0;
}
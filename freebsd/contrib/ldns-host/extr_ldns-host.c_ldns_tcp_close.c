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
struct TYPE_3__ {scalar_t__ _socket; } ;
typedef  TYPE_1__ ldns_resolver ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 

__attribute__((used)) static void
ldns_tcp_close(ldns_resolver *res) {
    if (res->_socket > 0) {
        close(res->_socket);
        res->_socket = 0;
    }
}
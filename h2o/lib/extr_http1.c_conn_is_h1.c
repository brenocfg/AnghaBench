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
struct TYPE_3__ {int /*<<< orphan*/ * callbacks; } ;
typedef  TYPE_1__ h2o_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  h1_callbacks ; 

__attribute__((used)) static int conn_is_h1(h2o_conn_t *conn)
{
    return conn->callbacks == &h1_callbacks;
}
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
struct connection {int dummy; } ;

/* Variables and functions */
 int __tl_fetch_init (struct connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tl_in_conn_methods ; 
 int /*<<< orphan*/  tl_type_conn ; 

int tl_fetch_init (struct connection *c, int size) {
  return __tl_fetch_init (c, 0, tl_type_conn, &tl_in_conn_methods, size);
}
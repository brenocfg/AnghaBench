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
struct htc_data {int /*<<< orphan*/  header_size; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 struct htc_data* HTC_DATA (struct connection*) ; 
 int SKIP_ALL_BYTES ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int /*<<< orphan*/ ) ; 

int htc_default_execute (struct connection *c, int op) {
  struct htc_data *D = HTC_DATA(c);

  vkprintf (1, "http_client_execute: op=%d, header_size=%d\n", op, D->header_size);

  return SKIP_ALL_BYTES;
}
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
 int mcc_default_check_perm (struct connection*) ; 

int mcc_crypto_check_perm (struct connection *c) {
  int x = mcc_default_check_perm (c);
  if (x > 0) {
    return 2;
  } else {
    return x;
  }
}